package logger

import (
	"log/syslog"
	"os"
	"path/filepath"

	"github.com/adrg/xdg"
	"github.com/tchap/zapext/v2/zapsyslog"
	"go.uber.org/zap"
	"go.uber.org/zap/zapcore"
)

func newLogger(name string) *zap.SugaredLogger {

	var (
		err    error
		config zapcore.EncoderConfig
		option zap.Option
	)

	logMode := os.Getenv("LOG_MODE")
	switch logMode {
	case "develop":
		config = zap.NewDevelopmentEncoderConfig()
		option = zap.AddStacktrace(zap.WarnLevel)
	default:
		config = zap.NewProductionEncoderConfig()
		option = zap.AddStacktrace(zap.ErrorLevel)
	}

	logLevelEnv := os.Getenv("LOG_LEVEL")
	consoleLevel := zap.NewAtomicLevel()
	err = consoleLevel.UnmarshalText([]byte(logLevelEnv))
	if err != nil {
		panic(err)
	}

	logFile, err := os.OpenFile(filepath.Join(xdg.CacheHome, name+".log"), os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0660)
	if err != nil {
		panic(err)
	}

	syslogWriter, err := syslog.New(syslog.LOG_USER, "")
	if err != nil {
		panic(err)
	}

	core := zapcore.NewTee(
		zapcore.NewCore(zapcore.NewConsoleEncoder(config), zapcore.Lock(os.Stderr), consoleLevel),
		zapcore.NewCore(zapcore.NewJSONEncoder(config), zapcore.Lock(logFile), zap.WarnLevel),
		zapsyslog.NewCore(zapcore.WarnLevel, zapcore.NewJSONEncoder(config), syslogWriter),
	)

	logger := zap.New(core, option)

	slogger := logger.Named(name).Sugar()

	return slogger
}
