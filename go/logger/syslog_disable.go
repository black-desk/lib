//go:build windows || plan9

package logger

func getSyslogCore(config zapcore.EncoderConfig) zapcore.Core {
        return nil
}
