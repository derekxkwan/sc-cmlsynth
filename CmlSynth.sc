

CmlSynth : UGen {
	* ar {
		arg bufsize = 100, eps = 0.5, omega = 0, k = 0, mul = 1.0, add = 0.0;
		^this.multiNew('audio',bufsize,eps,omega,k).madd(mul, add)
	}
}
