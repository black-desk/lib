package logger

import (
	"os"
	"path/filepath"

	"github.com/adrg/xdg"
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

	cores := []zapcore.Core{
		zapcore.NewCore(
			zapcore.NewConsoleEncoder(consoleConfig),
			zapcore.Lock(os.Stderr),
			consoleLevel,
		),
	}

	err = os.MkdirAll(xdg.CacheHome, 0755)
	if err == nil {
		err = addFileCore(name, &cores, &jsonConfig)
	}

	// NOTE(black_desk): Syslog is not implemented in windows and plan9.
	// https://stackoverflow.com/questions/42083059/getting-syslog-writer-undefined
	syslogCore := getSyslogCore(jsonConfig)
	if syslogCore != nil {
		cores = append(cores, syslogCore)
	}

	core := zapcore.NewTee(cores...)

	log := zap.New(core, options...).Named(name).Sugar()
	if err != nil {
		log.Warnf("failed to create log file for logger \"%s\": %v", name, err)
	}
	return log
}

func addFileCore(name string, cores *[]zapcore.Core, config *zapcore.EncoderConfig) error {
	logFile, err := os.OpenFile(
		filepath.Join(xdg.CacheHome, name+".log"),
		os.O_APPEND|os.O_CREATE|os.O_WRONLY,
		0660,
	)

	if err == nil {
		*cores = append(*cores,
			zapcore.NewCore(
				zapcore.NewJSONEncoder(*config),
				zapcore.Lock(logFile),
				zap.WarnLevel,
			),
		)
	}

	return err
}
