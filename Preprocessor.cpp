void Preprocessor::preprocess(const char *dest, const char *src)
{
	FILE *fFrom = fopen(src, "r");
	if (fFrom == NULL) {
		perror("ERROR: Cannot open source file\n");
	}
	FILE *fTo = fopen(dest, "w");
	if (fTo == NULL) {
		perror("ERROR: Cannot open destination file %s\n");
	}
	char ch;
	bool doubleSlashed = false;
	bool blocked = false;
	bool stringed = false;
	char last = 0;
	while ((ch = fgetc(fFrom)) != EOF) {
		if (doubleSlashed) {
			if (ch == '\n') {
				doubleSlashed = false;
				fputc('\n', fTo);
				last = 0;
				continue;
			}
		} 
		else if (blocked) {
			if (ch == '/') {
				if (last == '*') {
					blocked = false;
					last = 0;
					continue;
				}
			}
			else if (ch == '\n') {
				fputc('\n', fTo);
			}
		}
		else if (stringed) {
			fputc(ch, fTo);
			if (ch == '\"') {
				stringed = false;
				last = 0;
				continue;
			}
		}
		else {
			if (ch == '/') {
				if (last == '/') {
					doubleSlashed = true;
					last = 0;
					continue;
				} 
			}
			else if (ch == '*') {
				if (last == '/') {
					blocked = true;
					last = 0;
					continue;
				}
				else
				{
					fputc(ch, fTo);
				}
			}
			else if (ch == '\"') {
				fputc(ch, fTo);
				stringed = true;
				last = 0;
				continue;
			}
			else {
				if (last == '/') {
					fputc('/', fTo);
					printf("!!!\n");
				}
				fputc(ch, fTo);
			}
		}
		last = ch;
	}
	fclose(fFrom);
	fclose(fTo);

}
