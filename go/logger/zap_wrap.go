package logger

import (
	"log"
	"os"
	"strings"

	"github.com/black-desk/zap-journal/conn"
	"github.com/black-desk/zap-journal/encoder"
	"go.uber.org/zap"
	"go.uber.org/zap/zapcore"
)

func newLogger(name string) *zap.SugaredLogger {

	cores := []zapcore.Core{}

	level := getLevel()

	encoderConfig, options := getZapEncoderConfigAndOptions()

	func() {
		if !stderrIsTerminal() {
			return
		}

		consoleCore, err := newConsoleCore(encoderConfig, level)
		if err != nil {
			log.Default().Printf(
				"Failed to create console zapcore: %s",
				err.Error(),
			)
		} else {
			cores = append(cores, consoleCore)
		}
	}()

	{
		journalCore, err := newJournalCore(encoderConfig, level)
		if err != nil {
			log.Default().Printf(
				"Failed to create journal zapcore: %s",
				err.Error(),
			)
		} else {
			cores = append(cores, journalCore)
		}
	}

	if len(cores) == 0 {
		cores = append(cores,
			zapcore.NewCore(zapcore.NewJSONEncoder(
				zap.NewDevelopmentEncoderConfig(),
			), zapcore.Lock(os.Stderr), level),
		)
	}

	core := zapcore.NewTee(cores...)

	log := zap.New(core, options...).Named(name).Sugar()
	return log
}

func getZapEncoderConfigAndOptions() (
	encoderConfig zapcore.EncoderConfig,
	options []zap.Option,
) {
	logMode := os.Getenv("LOG_MODE")
	logMode = strings.ToLower(logMode)

	switch logMode {
	case "develop":
		encoderConfig = zap.NewDevelopmentEncoderConfig()
		options = []zap.Option{
			zap.Development(),
			zap.AddStacktrace(zap.WarnLevel),
		}
	default:
		encoderConfig = zap.NewProductionEncoderConfig()
		options = []zap.Option{
			zap.AddStacktrace(zap.ErrorLevel),
		}
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
