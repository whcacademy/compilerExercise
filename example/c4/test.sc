read x;;
if x == 0
	print 1;
else
	if (x >= 1 && x<12){
		f = 1;
		while(x > 1){
			f = f * +x;
			x = x-1;
		}
		print f;
	}