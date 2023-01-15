package errwrap

import (
	"fmt"
	"runtime"
)

func Trace(err error, annotate ...any) error {
	return trace(2, err, annotate...)
}

func trace(level int, err error, annotate ...any) error {
	if err == nil {
		return nil
	}

	_, file, line, ok := runtime.Caller(level)
	if !ok {
		panic("failed to get caller")
	}

	msg := formatAnnotate(annotate)

	return fmt.Errorf("%s:%d"+msg+"\n%w", file, line, err)
}

func formatAnnotate(annotate []any) string {
	if len(annotate) == 0 {
		return ""
	}

	msg, ok := annotate[0].(string)
	if !ok {
		panic("annotate should start with string")
	}

	return fmt.Sprintf(" [ "+msg+" ]", annotate[1:]...)
}

func Annotate(err error, message string, a ...any) error {
	return trace(2, err, append([]any{message}, a...)...)
}
