package logger

import (
	"errors"
	"go.uber.org/zap/zapcore"
)

func getSyslogCore(config zapcore.EncoderConfig) (zapcore.Core, error) {
	return nil, errors.New("syslog is not implemented on windows")
}
