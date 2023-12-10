# 프로젝트 설명
쓰레드(또는 프로세스)가 자원을 공유하는 상황을 구현 했고, 그 상황은 아래와 같습니다.  
n명의 철학자는 원형 식탁에서 식사를 하며, 각 철학자 사이에는 포크가 하나씩 놓여 있습니다. (따라서 포크는 n개 입니다.)  
철학자가 식사를 하기 위해서는 철학자 양 옆에 존재하는 포크를 하나씩 모두 잡아야 식사를 할 수 있습니다.  
철학자들은 다음의 과정을 통해 식사를 합니다.

1. 일정 시간 생각을 한다.
2. 양쪽의 포크를 잡으면 일정 시간만큼 식사를 한다.
3. 양쪽의 포크를 내려놓는다.
4. 다시 1번으로 돌아간다.

자원을 공유하는 과정에서 교착상태와 기아상태가 발생합니다.  
교착상태 : 우연히 모든 철학자들이 자기 왼쪽 포크를 잡고 있다면, 모든 철학자들이 자기 오른쪽의 포크가 사용 가능해질 때까지 기다려야 합니다.  
기아상태 : 결국, 포크를 사용할때까지 기다리다가 모든 철학자는 양쪽 포크를 잡지 못하고 아무것도 진행할 수 없는 상태가 됩니다.

[자세한 식사하는 철학자 문제 설명](https://namu.wiki/w/%EC%8B%9D%EC%82%AC%ED%95%98%EB%8A%94%20%EC%B2%A0%ED%95%99%EC%9E%90%20%EB%AC%B8%EC%A0%9C)

# 프로젝트 목표

1. 뮤텍스와 세마포어를 활용하여 쓰레드(또는 프로세스) 동기화 처리
2. 쓰레드(또는 프로세스) 동기화로 교착상태와 기아상태 해결

# 기술스택
- C
- Makefile

# 프로젝트 구현 내용
### philo_one: 멀티 쓰레드 환경에서 뮤텍스로 쓰레드 동기화 처리
1. pthread_mutex_init() 함수 호출로 n개의 뮤텍스 생성
2. pthread_create() 함수 호출로 n개의 철학자(쓰레드) 생성
3. 각각의 철학자(쓰레드)는 포크(공유자원)를 사용하기전에 pthread_mutex_lock() 호출
   - 누군가 포크(공유자원)를 사용중이면 뮤텍스가 unlock 상태가 될때까지 대기
4. 각각의 철학자(쓰레드)는 포크(공유자원)를 다 사용하면 pthread_mutex_unlock() 호출
   - 대기 중인 철학자(쓰레드)가 포크(공유자원)를 사용

### philo_two: 멀티 쓰레드 환경에서 세마포어로 쓰레드 동기화 처리
1. sem_open() 함수 호출로 세마포어(세마포어 수: n / 2) 생성
2. pthread_create() 함수 호출로 n개의 철학자(쓰레드) 생성
3. 각각의 철학자(쓰레드)는 포크(공유자원)를 사용하기전에 sem_wait() 호출
   - 세마포어 수가 0이 아니면 세마포어 수가 0이 될때까지 대기
4. 각각의 철학자(쓰레드)는 포크(공유자원)를 다 사용하면 sem_post() 호출
   - 대기 중인 철학자(쓰레드)가 포크(공유자원)를 사용

### philo_three: 멀티 프로세스 환경에서 세마포어로 프로세스 동기화 처리
1. sem_open() 함수 호출로 세마포어(세마포어 수: n / 2) 생성
2. fork() 함수 호출로 n개의 철학자(프로세스) 생성
3. 각각의 철학자(프로세스)는 포크(공유자원)를 사용하기전에 sem_wait() 호출
   - 세마포어 수가 0이 아니면 세마포어 수가 0이 될때까지 대기
4. 각각의 철학자(프로세스)는 포크(공유자원)를 다 사용하면 sem_post() 호출
   - 대기 중인 철학자(프로세스)가 포크(공유자원)를 사용
