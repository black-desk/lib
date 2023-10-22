package ginkgohelper

import (
	"fmt"
	"reflect"

	"github.com/onsi/ginkgo/v2"
)

func ContextTable(message string, entries ...any) {
	tableEntries := []*ContextTableEntryT{}
	var fn any
	for i := range entries {
		switch v := entries[i].(type) {
		case *ContextTableEntryT:
			tableEntries = append(tableEntries, v)
		case any:
			if fn != nil {
				panic("only one function is allowed in ContextTable")
			}
			fn = v
		}
	}

	for i := range tableEntries {
		ginkgo.Context(
			fmt.Sprintf(message, tableEntries[i].fmtArgs...),
			func() { runContextTableEntry(fn, tableEntries[i]) },
		)
	}
}

func runContextTableEntry(fn any, entry *ContextTableEntryT) {
	vfn := reflect.ValueOf(fn)
	for j := range entry.args {
		if entry.args[j].IsValid() {
			continue
		}

		entry.args[j] = reflect.New(vfn.Type().In(j)).Elem()
	}
	vfn.Call(entry.args)
}
