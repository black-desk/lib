//go:build !windows && !plan9

package logger

import (
	"log/syslog"

	"github.com/tchap/zapext/v2/zapsyslog"
	"go.uber.org/zap/zapcore"
)

func getSyslogCore(config zapcore.EncoderConfig) zapcore.Core {
	syslogWriter, err := syslog.New(syslog.LOG_USER, "")
	if err != nil {
		panic(err)
	}
	return zapsyslog.NewCore(
		zapcore.WarnLevel,
		zapcore.NewJSONEncoder(config),
		syslogWriter,
	)
}
