#include "philo_one.h"

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
		pthread_mutex_init(&g_table.fork[i], NULL);
		// ex)철학자가 5명일때 i가 0이면 철학자 번호는 1번, 포크는 0번, 4번 포크를 사용함
		g_philos[i].nbr = i + 1;  // 철학자 번호
		g_philos[i].eat = 0;
		g_philos[i].fork1 = i - 1;
		if (!i)  // i == 0
			g_philos[i].fork1 = g_table.num_philo - 1;
		g_philos[i].fork2 = i;
	}
	pthread_mutex_init(&g_table.m_msg, NULL);
	g_table.eat = 0;
	g_table.dead = 0;
	g_table.base_time = get_time();  // 0초가 되는시간 (기준이 되는 시간)
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
	int		i;

	i = -1;
	while (++i < g_table.num_philo)
		pthread_mutex_destroy(&g_table.fork[i]);
	pthread_mutex_destroy(&g_table.m_msg);
	free(g_table.fork);
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
	if (!(g_table.fork = malloc(sizeof(pthread_mutex_t) * g_table.num_philo)))
		return (printf("fork malloc error!"));
	init_table();
	init_philos();
	clean_table();
	return (0);
}
