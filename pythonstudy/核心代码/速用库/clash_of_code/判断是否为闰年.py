import calendar
year = int(input())
check_year = calendar.isleap(year)
if check_year == True:
	print(f'{year}年是闰年')
else:
	print(f'{year}年不是闰年')

