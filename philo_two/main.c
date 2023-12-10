#include "philo_two.h"

// 문자열로 들어오는 인자를 정수형으로 파싱
int		parse(char **argv)
{
	// 인자가 음수이면 에러처리
	if (ft_atoi(argv[1]) <= 1 ||
		ft_atoi(argv[2]) <= 0 ||
		ft_atoi(argv[3]) <= 0 ||
		ft_atoi(argv[4]) <= 0 ||
		(argv[5] && ft_atoi(argv[5]) <= 0))
		return (1);
	g_table.num_philo = ft_atoi(argv[1]);
	g_table.time_to_die = ft_atoi(argv[2]);
	g_table.time_to_eat = ft_atoi(argv[3]);
	g_table.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		g_table.num_eat = ft_atoi(argv[5]);
	else
		g_table.num_eat = -1;
	// 변수가 unsigned long 이라서 조건문에서 음수를 잡아주지 못했음
	// if ((g_table.num_philo = ft_atoi(argv[1])) <= 1 ||
	// 	(g_table.time_to_die = ft_atoi(argv[2])) <= 0 ||
	// 	(g_table.time_to_eat = ft_atoi(argv[3])) <= 0 ||
	// 	(g_table.time_to_sleep = ft_atoi(argv[4])) <= 0)
	// 	return (1);
	// if (argv[5] && (g_table.num_eat = ft_atoi(argv[5])) <= 0)
	// 	return (1);
	// else if (!argv[5])
	// 	g_table.num_eat = -1;
	return (0);
}

void	init_table(void)
{
	int		i;

	i = -1;
	while (++i < g_table.num_philo)
	{
		g_philos[i].nbr = i + 1;  // 철학자 번호
		g_philos[i].eat = 0;
	}
	g_table.eat = 0;
	g_table.dead = 0;
	g_table.base_time = get_time();  // 0초가 되는시간 (기준이 되는 시간)
	g_table.enter = sem_open("/enter", O_CREAT | O_EXCL, 0777,
			g_table.num_philo / 2);  // 철학자수/2 만큼 세마포어값 설정
	g_table.m_msg = sem_open("/m_msg", O_CREAT | O_EXCL, 0777, 1);
	// sem_unlink : 세마포어를 제거하는 함수로 sem_close를 만날때까지 제거를 보류함
	sem_unlink("/enter");
	sem_unlink("/m_msg");
}

void	init_philos(void)
{
	int		i;

	i = -1;
	while (++i < g_table.num_philo)
	{
		g_philos[i].last_eat = get_time();  // 시뮬레이션을 시작한 시간으로 각 철학자들이 마지막으로 밥먹은 시간을 설정 
		pthread_create(&g_philos[i].tid, NULL, philo_act, &g_philos[i]);  // 철학자 숫자만큼 철학자가 행동하는 쓰레드를 만듬
	}
	i = -1;
	while (++i < g_table.num_philo)
		pthread_join(g_philos[i].tid, NULL);
}

void	clean_table(void)
{
	sem_close(g_table.enter);
	sem_close(g_table.m_msg);
	free(g_philos);
}

int		main(int argc, char **argv)
{
	// 인자가 4개나 5개가 아니면 에러처리
	// 인자의 값이 음수면 에러처리
	if (!(argc == 5 || argc == 6) || parse(argv))
		return (printf("argruments error!"));
	if (!(g_philos = malloc(sizeof(t_philo) * g_table.num_philo)))
		return (printf("philos malloc error!"));
	init_table();
	init_philos();
	clean_table();
	return (0);
}
