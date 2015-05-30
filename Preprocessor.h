#ifndef PREPROCESSOR
#define PREPROCESSOR
class Preprocessor
{
private:
	Preprocessor();
public:
	static void preprocess(const char *dest, const char *from);
};

#endif