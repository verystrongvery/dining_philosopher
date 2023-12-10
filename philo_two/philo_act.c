#include "philo_two.h"

// 메시지를 출력하는 함수
int		msg(t_philo *philo, int msg, unsigned long cur)
{
	sem_wait(g_table.m_msg);  // 세마포어로 락을 해줌으로써 메시지가 꼬이지 않게함
	if (g_table.dead)  // 이미 죽은 철학자가 있으면
	{
		sem_post(g_table.m_msg);
		return (1);  // 아무말도안하고 탈출. 1을 반환함으로써 philo_act의 반복문을 벗어나게함 
	}
	printf("%lu %d", cur - g_table.base_time, philo->nbr);
	if (msg == TAKEN_FORK)
		printf(" has taken a fork\n");
	else if (msg == EATING)
	{
		printf(" is eating\n");
		philo->last_eat = cur;   // 밥을먹었으니 마지막으로 밥먹은 시간을 갱신
	}
	else if (msg == SLEEPING)
		printf(" is sleeping\n");
	else if (msg == THINKING)
		printf(" is thinking\n");
	else if (msg == DEAD)
	{
		printf(" died\n");
		g_table.dead = 1;
	}
	sem_post(g_table.m_msg);  // 세마포어를 언락을 해줌으로써 락에 막혀있던 세마포어를 풀어줌
	return (0);
}

// 철학자 한명을 감시하는 쓰레드 함수
void	*philo_monitor(void *phi)
{
	t_philo			*philo;
	unsigned long	cur;

	philo = (t_philo *)phi;
	while (1)
	{
		if (philo->eat == g_table.num_eat)  // 한명의 철학자가 밥을 다먹으면
			break ;
		cur = get_time();
		if (g_table.time_to_die < cur - philo->last_eat)  // 밥을 못먹어서 죽게될경우
		{
			msg(philo, DEAD, cur);
			return (NULL);
		}
		less_error_sleep(1);  // 살짝 쉬면서 자원을 낭비하지않게함
	}
	return (NULL);
}

int		eat(t_philo *philo)
{
	// 세마포어를 락을 해줌으로써 철학자수/2값이 초과되지 않는 인원만 포크를들어 밥을 먹을 수 있음
	sem_wait(g_table.enter);
	msg(philo, TAKEN_FORK, get_time());
	msg(philo, TAKEN_FORK, get_time());
	msg(philo, EATING, get_time());
	less_error_sleep(g_table.time_to_eat);  // 먹는시간만큼 쉬기
	sem_post(g_table.enter);
	philo->eat++;  // 철학자가 밥먹은 횟수 증가
	if (philo->eat == g_table.num_eat)
	{
		g_table.eat++;  // 다먹은 철학자의 수 1증가
		return (1);  // 1을 리턴함으로써 philo_act함수의 반목문을 탈출
	}
	return (0);
}

void	*philo_act(void *phi)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)phi;
	pthread_create(&tid, NULL, philo_monitor, philo);  // 한 철학자를 감시하는 쓰레드함수 생성 
	while (1)
	{
		if (eat(philo))  // 밥먹고
			break ;
		if (msg(philo, SLEEPING, get_time()))  // 잠자고
			break ;
		less_error_sleep(g_table.time_to_sleep);
		if (msg(philo, THINKING, get_time()))  // 생각하고
			break ;
	}
	pthread_join(tid, NULL);
	return (NULL);
}
