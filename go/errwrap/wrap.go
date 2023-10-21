//go:build !debug
// +build !debug

package errwrap

import (
	"fmt"
)

func formatAnnotate(annotate []any) string {
	if len(annotate) == 0 {
		return ""
	}

	msg, ok := annotate[0].(string)
	if !ok {
		panic("annotate should start with string")
	}

	return fmt.Sprintf(msg, annotate[1:]...)
}

func Wrap(err *error, annotate ...any) {
	if err == nil || *err == nil {
		return
	}

	msg := formatAnnotate(annotate)

	if msg != "" {
		*err = fmt.Errorf(msg+": %w", *err)
	}

	return
}
