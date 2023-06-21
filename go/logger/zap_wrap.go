package logger

import (
	"log"
	"os"

	"github.com/black-desk/zap-journal/conn"
	"github.com/black-desk/zap-journal/encoder"
	"go.uber.org/zap"
	"go.uber.org/zap/zapcore"
)

func newLogger(name string) *zap.SugaredLogger {
	cores := []zapcore.Core{}

	level := getLevel()

	encoderConfig, options := getZapEncoderConfigAndOptions()

	if stderrIsTerminal() {
		consoleCore, err := newConsoleCore(encoderConfig, level)
		if err != nil {
			log.Default().Printf(
				"Failed to create console zapcore: %s.",
				err.Error(),
			)
		} else {
			cores = append(cores, consoleCore)
		}
	}

	journalCore, err := newJournalCore(encoderConfig, level)
	if err != nil {
		log.Default().Printf(
			"Failed to create journal zapcore: %s.",
			err.Error(),
		)
	} else {
		cores = append(cores, journalCore)
	}

	if len(cores) == 0 {
		log.Default().Print(
			"Fallback to zap default development logger.",
		)

		zapDevelopmentCore := zapcore.NewCore(
			zapcore.NewJSONEncoder(
				zap.NewDevelopmentEncoderConfig(),
			),
			zapcore.Lock(os.Stderr),
			level,
		)
		cores = append(cores, zapDevelopmentCore)
	}

	core := zapcore.NewTee(cores...)

	log := zap.New(core, options...).Named(name).Sugar()
	return log
}

// https://rosettacode.org/wiki/Check_output_device_is_a_terminal#Go
func stderrIsTerminal() bool {
	fileInfo, _ := os.Stderr.Stat()
	return (fileInfo.Mode() & os.ModeCharDevice) == os.ModeCharDevice
}

func newConsoleCore(
	encoderConfig zapcore.EncoderConfig, level zap.AtomicLevel,
) (
	core zapcore.Core, err error,
) {
	core = zapcore.NewCore(
		zapcore.NewConsoleEncoder(encoderConfig),
		zapcore.Lock(os.Stderr),
		level,
	)
	return
}

func newJournalCore(
	encoderConfig zapcore.EncoderConfig, level zap.AtomicLevel,
) (
	core zapcore.Core, err error,
) {
	encoderConfig.StacktraceKey = "STACKTRACE"

	enc, err := encoder.New(encoder.WithCfg(encoderConfig))
	if err != nil {
		return
	}

	sink, err := conn.New(conn.WithAddress("/run/systemd/journal/socket"))
	if err != nil {
		return
	}

	core = zapcore.NewCore(
		enc, sink, level,
	)
	return
}
