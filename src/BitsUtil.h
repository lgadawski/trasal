#ifndef BITSUTIL_H_
#define BITSUTIL_H_

class BitsUtil {
private:
	BitsUtil() {} // prevent instatiations
public:
	static int GetNumberOfBitsNeedToRepresentValue(int val) {
		int count = 0;
		while (val > 0) {
		    count++;
		    val = val >> 1;
		}

		return count;
	}
};

#endif /* BITSUTIL_H_ */
