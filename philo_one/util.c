#include "philo_one.h"

int				ft_atoi(char *str)
{
	int		i;
	int		ret;
	int		sign;

	sign = 1;
	ret = 0;
	i = -1;
	if (str[i + 1] == '-' && i++)
		sign = -1;
	while (str[++i])
	{
		if (str[i] < '0' || '9' < str[i])
			return (-1);
		ret = ret * 10 + (str[i] - '0');
	}
	return (sign * ret);
}

unsigned long	get_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);  // s와 us을 ms단위로 변환
}

// usleep을 오차가 적게 사용하기위한 함수
// usleep(100) 이면, 사실 100us이상 sleep을 함. 오차가 있음
// usleep(100)을 10번돌리는것이 usleep(1000)을 한번돌리는것보다 오차가 적음 
void			less_error_sleep(unsigned long input)
{
	unsigned long	base;
	unsigned long	cur;

	base = get_time();
	while (1)
	{
		cur = get_time();
		if (input < cur - base)
			return ;
		usleep(100);
	}
}
