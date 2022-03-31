namespace quantum_rng {

    open Microsoft.Quantum.Canon;
    open Microsoft.Quantum.Intrinsic;
    open Microsoft.Quantum.Measurement;
    open Microsoft.Quantum.Math;
    open Microsoft.Quantum.Convert;

    operation GenerateRandomBit() : Result {
        // allocate a qubit.
        use q = Qubit();
        // put the qubit in superposition.
        H(q);
        // it now has a 50% chance of being measured 0 or 1.
        // Measure the value.
        return M(q);
    }

    operation sample_random_in_range(max:Int) : Int {
        mutable output = 0;
        repeat {
            mutable bits = new Result[0];
            for idxBit in 1..BitSizeI(max) {
                set bits += [GenerateRandomBit()];
            }
            set output = ResultArrayAsInt(bits);
        } until ( output <= max);
        return output;
    }

    @EntryPoint()
    operation SampleRandomNumber() : Int {
        let max = 50;
        Message($"sampling 0 to {max}: ");
        return sample_random_in_range(max);
    }
}
