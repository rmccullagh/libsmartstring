## SmartString
A "smart" string buffer for C. Why is it smart? It automatically resizes itself to fit any size string. It has an easy API for dynamic strings.

`SmartString* smart_string_new(void)`

**DESCRIPTION**

Create a new `SmartString` instance

**RETURN VALUE**

`SmartString` object, or NULL if allocating it fails.

`bool smart_string_append(SmartString* ss, const char* str)`

**DESCRIPTION**

Appends the value of `str` to the end of the current buffer

**RETURN VALUE**

true if `str` was able to appended to the current `SmartString` buffer. Otherwise it returns false.

`bool smart_string_append_sprintf(SmartString* ss, const char* format, ...)`

**DESCRIPTION**

Append a formated string to the `SmartString` buffer. Taking a variable argument list, it internally calls vsnprintf with
a locally allocated buffer. It will continue to resize the locally allocated buffer if `vsnprintf` indicates that the resulting string
was truncated. The locally allocated buffer is freed before the function returns to the caller.

**RETURN VALUE**

true if the format and arguments were able to appended to the `SmartString` buffer. Otherwise it returns false.

`bool smart_string_starts_with(SmartString* ss, const char* str)`

**DESCRIPTION**

Checks to see if the buffer is equal to `str`

**RETURN VALUE**

true if the string `str` is equal to the `SmartString` buffer. Otherwise it returns false.

`void smart_string_destroy(SmartString* ss)`

**DESCRIPTION**

Destroys a `SmartString` instance and releases any memory allocated.
