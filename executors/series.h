
class series{

public:
    explicit series(int initial_value, unsigned int n = 1)
        : _initial(initial_value), _n(n) {}

    int operator()() {
        int result = _initial;
        for (int counter = 1; counter <= _n; ++counter) {
            if ( counter%3 == 0 ) {
                result = -1*result + 3*counter;
            } else {
                result = result - 2*counter;
            }
        }
        return result;
    }

    constexpr int initial() const { return _initial; }
    constexpr unsigned int n() const { return _n; }

    int operator<=>(const series&) const = default;

private:
    int          _initial = 0;
    unsigned int _n = 1;

};


