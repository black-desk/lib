//go:build windows || plan9

package logger

import (
	"go.uber.org/zap/zapcore"
)

func getSyslogCore(config zapcore.EncoderConfig) zapcore.Core {
	return nil
}
