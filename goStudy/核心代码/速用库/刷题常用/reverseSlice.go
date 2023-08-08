
func reverseSlice[T bool | int | int8 | int16 | int32 | int64 | uint8 | uint16 | uint32 | uint64 | uintptr | float32 | float64 | complex64 | complex128 | string](slices []T) []T {
	length := len(slices)
	reverseAfterSlice := slices
	for i := 0; i < length/2; i++ {
		reverseAfterSlice[i], reverseAfterSlice[length-1-i] = reverseAfterSlice[length-1-i], reverseAfterSlice[i]
	}
	return reverseAfterSlice
}