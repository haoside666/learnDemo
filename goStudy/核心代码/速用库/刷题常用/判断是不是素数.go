func isp(n int) bool {
	flagss := true
	for i := 2; i <= int(math.Ceil(math.Sqrt(float64(n)))); i++ {
		if n%i == 0 {
			flagss = false
			break
		}
	}
	return n > 1 && flagss
}