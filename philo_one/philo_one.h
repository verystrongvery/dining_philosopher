#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>

# define TAKEN_FORK	0
# define EATING		1
# define SLEEPING	2
# define THINKING	3
# define DEAD		4

typedef struct		s_table
{
	int				num_philo;  // 철학자수 = 포크수
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				num_eat;

	unsigned long	base_time;  // 기준이 되는시간
	int				eat;  // 다먹은 철학자의 수
	int				dead;  // 철학자가 한명이라도 죽으면 1이되는 변수
	pthread_mutex_t	*fork;  // 철학자의 수만큼 만들 포크 뮤텍스
	pthread_mutex_t	m_msg;  // 메시지를 출력할때 꼬이지말라고 만드는 뮤텍스
}					t_table;

typedef struct		s_philo
{
	int				nbr;  // 철학자번호
	int				fork1;
	int				fork2;
	int				eat;  // 철학자가 먹은 횟수
	unsigned long	last_eat;  // 철학자가 마지막으로 밥먹은 시간
	pthread_t		tid;  // 철학자 쓰레드 아이디
}					t_philo;

t_table				g_table;  // 전역변수로 테이블 선언
t_philo				*g_philos;  // 전역변수로 철학자 선언

void				*philo_act(void *philo);
void				*philo_monitor(void *philo);
void				clean_table(void);
void				less_error_sleep(unsigned long time);
void				init_philos(void);
void				init_table(void);

int					ft_atoi(char *str);
int					parse(char **argv);
int					msg(t_philo *philo, int msg, unsigned long cur);
int					eat(t_philo *philo);

unsigned long		get_time(void);

#endif
