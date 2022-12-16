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
		err    error
		config zap.Config
	)

	logMode := os.Getenv("LOG_MODE")
	if logMode == "develop" {
		config = zap.NewDevelopmentConfig()
		config.EncoderConfig.EncodeLevel = zapcore.CapitalColorLevelEncoder
	} else {
		config = zap.NewProductionConfig()
		config.OutputPaths = []string{filepath.Join(xdg.CacheHome, name+"_log.json")}
		config.ErrorOutputPaths = []string{filepath.Join(xdg.CacheHome, name+"_log.json")}
	}

	logLevelEnv := os.Getenv("LOG_LEVEL")
	err = config.Level.UnmarshalText([]byte(logLevelEnv))
	if err != nil {
		panic(err)
	}

	var logger *zap.Logger

	logger, err = config.Build()
	if err != nil {
		panic(err)
	}

	slogger := logger.Named(name).Sugar()

	return slogger
}
