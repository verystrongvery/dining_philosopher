#include "philo_three.h"

// 모든 자식프로세스를 죽이는 함수
int		kill_process(void)
{
	int		i;

	i = -1;
	while (++i < g_table.num_philo)
		kill(g_philos[i].pid, SIGKILL);
	return (1);
}

void	process_monitor(void)
{
	int		i;
	int		status;
	int		eat;

	eat = 0;
	while (1)
	{
		i = -1;
		while (++i < g_table.num_philo)
		{
			status = -1;
			// waitpid의 마지막 인자가 WNOHANG이면 자식프로세스를 기다리지 않고 일단 그냥 넘어감
			// 자식프로세스가 종료되지 않으면 status 값을 변경하지 않음
			// 자식프로세스가 종료가되면 status에 자식프로세스의 반환값*256이 저장이됨
			waitpid(g_philos[i].pid, &status, WNOHANG);
			if (status == 256)  // 자식프로세스 반환값이 1일때 = 철학자가 굶어 죽은상황
				break ;
			if (status == 0 && ++eat)  // 자식프로세스 반환값이 0일때 = 한철학자가 밥을 다먹은 상황
				if (eat == g_table.num_philo)  // 모든 철학자가 밥을 다먹었으면
					break ;
		}
		if (i != g_table.num_philo)  // 프로그램이 다 끝나면
		{
			kill_process();  // 자식 프로세스 다죽이기
			break ;
		}
	}
}
