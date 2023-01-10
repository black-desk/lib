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
		err     error
		options []zap.Option
	)

	logMode := os.Getenv("LOG_MODE")
	switch logMode {
	case "develop":
		options = []zap.Option{
			zap.Development(),
			zap.AddStacktrace(zap.WarnLevel),
		}
	default:
		options = []zap.Option{zap.AddStacktrace(zap.ErrorLevel)}
	}

	consoleConfig := zap.NewDevelopmentEncoderConfig()
	consoleConfig.EncodeLevel = zapcore.CapitalColorLevelEncoder

	jsonConfig := zap.NewProductionEncoderConfig()

	logLevelEnv := os.Getenv("LOG_LEVEL")
	consoleLevel := zap.NewAtomicLevel()
	err = consoleLevel.UnmarshalText([]byte(logLevelEnv))
	if err != nil {
		panic(err)
	}

	logFile, err := os.OpenFile(
		filepath.Join(xdg.CacheHome, name+".log"),
		os.O_APPEND|os.O_CREATE|os.O_WRONLY,
		0660,
	)
	if err != nil {
		panic(err)
	}

	syslogWriter, err := syslog.New(syslog.LOG_USER, "")
	if err != nil {
		panic(err)
	}

	core := zapcore.NewTee(
		zapcore.NewCore(
			zapcore.NewConsoleEncoder(consoleConfig),
			zapcore.Lock(os.Stderr),
			consoleLevel,
		),
		zapcore.NewCore(
			zapcore.NewJSONEncoder(jsonConfig),
			zapcore.Lock(logFile),
			zap.WarnLevel,
		),
		zapsyslog.NewCore(
			zapcore.WarnLevel,
			zapcore.NewJSONEncoder(jsonConfig),
			syslogWriter,
		),
	)

	logger := zap.New(core, options...)

	slogger := logger.Named(name).Sugar()

	return slogger
}
