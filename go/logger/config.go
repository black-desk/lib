//go:build !debug
// +build !debug

package logger

import (
	"os"

	"go.uber.org/zap"
	"go.uber.org/zap/zapcore"
)

func getZapEncoderConfigAndOptions() (
	encoderConfig zapcore.EncoderConfig,
	options []zap.Option,
) {
	encoderConfig = zap.NewProductionEncoderConfig()
	options = []zap.Option{
		zap.AddStacktrace(zap.ErrorLevel),
	}

	return
}

func getLevel() zap.AtomicLevel {
	logLevelEnv := os.Getenv("LOG_LEVEL")
	logLevel := zap.NewAtomicLevel()
	err := logLevel.UnmarshalText([]byte(logLevelEnv))
	if err != nil {
		panic(err)
	}
	return logLevel
}
