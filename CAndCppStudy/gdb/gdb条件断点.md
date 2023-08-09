```c
	 1  #include <stdio.h>
     2	
     3	int func(int n)
     4	{
     5		int sum=0,i;
     6		for(i=0;i<n;i++)
     7		{
     8			sum +=i;
     9		}
    10		return sum;
    11	}
    12	
    13	
    14	int main(int argc,char *argv[])
    15	{
    16		unsigned int i;
    17		long result;
    18		for(i=1;i<100;i++)
    19		{
    20			result +=i;
    21		}
    22		printf("result[1-100]=%d\n",result);
    23		printf("result[1-250]=%d\n",func(250));
    24		return 0;
    25	}
```

当i=50时停止

b 18 if i=50