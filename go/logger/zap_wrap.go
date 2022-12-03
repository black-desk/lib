package logger

import (
	"os"

	"go.uber.org/zap"
	"go.uber.org/zap/zapcore"
)

func newLogger(name string) *zap.SugaredLogger {

	var err error

	config := zap.NewDevelopmentConfig()
	config.EncoderConfig.EncodeLevel = zapcore.CapitalColorLevelEncoder

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

	loggerMap.Store(name, slogger)

	return slogger
}
