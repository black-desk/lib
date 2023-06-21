//go:build debug
// +build debug

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
	encoderConfig = zap.NewDevelopmentEncoderConfig()
	options = []zap.Option{
		zap.Development(),
		zap.AddStacktrace(zap.WarnLevel),
	}

	return
}

func getLevel() zap.AtomicLevel {
	logLevelEnv := os.Getenv("LOG_LEVEL")
	if logLevelEnv == "" {
		logLevelEnv = "debug"
	}
	logLevel := zap.NewAtomicLevel()
	err := logLevel.UnmarshalText([]byte(logLevelEnv))
	if err != nil {
		panic(err)
	}
	return logLevel
}
