package main

import "fmt"

// Goat.
func goat(food int) (poop string) {

	food = food ^ 0x33bee6
	c := "^" + "][n" +
		"_" + "]" +
		"_" + "n" +
		"^]" + "[n" +
		"^]" + "[n" +
		"^]" + "[n" +
		"^Y[" + "n^@" + "ZJr" + "TCv" +
		"V]A\\nX;" + "Y\\JP^ZmSN^ERffTRvRXKZ=" + "Kkztxz<[" +
		"_RN^DRFbTRvVIAX<ikY\\xr<[oCN^ERffXX?VMIZ<ik>Fzz<[_BN^ERJS" +
		"xIovYC\\nXq\\Nxp_[_SN^][n^?[n?][n^][n^][n^]Sn^LJLRNnLSl" +
		"JN" + "?????????y[n^QSj^QG>^?[n^][N_QAbLU[" + "n^" +
		"U[fNUC?>?QdRASL_TKnRL[n^Q[fNQKo??;`" +
		"\\T[L>TKl^\\[n^U[fNUR??=?`\\UKM^TKN" +
		"^\\[n^U[j^USM>]WxL]R\\RDJn^\\[n^][n" +
		"^][oR" + "]YsdQOn^U[NLM[n" + "^][n^" + "][o" + "^L;bi" + "d[n\\" + "][lPQ" +
		"[>^" + "QSDFUQwL]JfNv" + ";NN" + "" + "" + "]" + "K" + "l" + "^" + "Q" + "S" +
		">^Y" + "ZfJUSvNU[@LT;N?" + "=o<" + "" + "" + "" + "" + "?qw>^" + "YKbBUUn" + "NU[bLR[" +
		"N>=kplqs>^X[dFUWfNU[jLZQBmqe" + "" + "" + "" + "p" + "m" + "q" + "w" + ">" + "^" +
		"X[dNUsfL??;=xQbLqQ`LQSn_>;" + "l^_" + "" + "" + "[n^_[" + "j" + "M" + "x" + "A" +
		"bmqQ@LQ[n^M_?w=ZLRNJN^iAb" +
		"LQQBlQ_n^E[fHDInN_SlPqA" + "bLqQF" + "lQ_n^" + "AYfN]" +
		"SfN=SnTQBbDAtZmq_n^ESfL" + "]" + "Q" + "f" + "O" + "=" + "S" +
		"nPQX" + "bHqp" + "zlu[n^T" + "CFN]SfO" + "][nZQXB" +
		"Hqdzm" + "u_n^U" + "J" + "f" + "l" + "U" + "S" + "f" +
		"MUSnZAYFHqAjLU[n^" + "]" + "Z" + "n" + ">" + "]" + "[" +
		"n>][n^AYd" +
		"rlQfLQ[n^]K" + "n_][o>][n^@YfW]YfLQ[n^]Kn_][o^][n\\TIfZ]Yf\\Q[n"

	var mbs = map[bool]string{false: "  ", true: "██"}

	var mib = map[int]byte{0: 56, 1: 7}

	for i := 0; i < len(c)<<1; i++ {
		if i%48 > 0 {

			var shift = 6 * (i >> 1 & 3) // 0, 0, 6, 6, 12, 12, 18, 18, 0, 0, ...
			var aa = byte(food >> shift)

			var bb = mib[i&1] // 0, 1, 0, 1, 0, 1, ....
			// turns into 110110, 111, 110110, 111, 110110, 111, .....

			var cc = c[i>>1] // 0, 0, 1, 1, 2, 2, 3, 3, .......

			poop += mbs[aa&bb&cc > 0]

		} else { //
			poop += "" + "\n" /*>     beef    &<*/
		}
	}

	return
}

func main() {
	var aa int = 13
	aa *= 3
	fmt.Println(goat(12233386))

	fmt.Println("")
	fmt.Println("")
	fmt.Println("")

	fmt.Println(goat(204276))

	fmt.Println("")
	fmt.Println("")
	fmt.Println("")

	fmt.Println(goat(0xf00d))

}
