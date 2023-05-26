package logger

import (
	"fmt"
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

	errs := []error{}
	fileCore, err := getFileCore(name, &jsonConfig)
	if err != nil {
		errs = append(errs,
			fmt.Errorf("Failed to init file logger: %w", err))
	} else {
		cores = append(cores, fileCore)
	}

	syslogCore, err := getSyslogCore(jsonConfig)
	if err != nil {
		errs = append(errs,
			fmt.Errorf("Failed to init syslog logger: %w", err))
	} else {
		cores = append(cores, syslogCore)
	}

	core := zapcore.NewTee(cores...)

	log := zap.New(core, options...).Named(name).Sugar()
	for i := range errs {
		log.Warn(errs[i])
	}
	return log
}

func getFileCore(name string, config *zapcore.EncoderConfig) (zapcore.Core, error) {
	err := os.MkdirAll(xdg.CacheHome, 0755)
	if err != nil {
		return nil, err
	}

	logFile, err := os.OpenFile(
		filepath.Join(xdg.CacheHome, name+".log"),
		os.O_APPEND|os.O_CREATE|os.O_WRONLY,
		0660,
	)

	if err != nil {
		return nil, err
	}

	return zapcore.NewCore(
		zapcore.NewJSONEncoder(*config),
		zapcore.Lock(logFile),
		zap.WarnLevel,
	), nil

}
