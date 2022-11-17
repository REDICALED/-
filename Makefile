NAME = minishell

SRC_DIR	:= ./srcs
INC_DIR	:= ./includes
OBJ_DIR	:= ./objects
LIB_DIR	:= ./libft

SRC = main.c \
		utils.c \
		tokenize.c \
		tokenize_count.c \
		tokenize_count2.c \
		hoo.c \
		hoo_here_doc.c \
		hoo_dollar.c \
		hoo_double_quote.c \
		hoo_string.c \
		redirection.c \
		redirection_utils.c \
		builtin.c \
		builtin2.c \
		builtin_export.c \
		execute.c \
		execute_single.c \
		execute_pipe.c \
		execve.c \
		signal.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

OBJ := $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_DIR)
#$(CC) $(OBJ) -L $(LIB_DIR) -lreadline -l ft -o $(NAME)
#$(CC) $(OBJ) -L $(LIB_DIR) -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -l ft -o $(NAME)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L $(LIB_DIR) -l ft -L /Users/jinhokim/.brew/opt/readline/lib/ -l readline

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -I$(INC_DIR) -I/Users/jinhokim/.brew/opt/readline/include/ -o $@ -c $<

clean:
	rm -rf $(OBJ)
	make -C $(LIB_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIB_DIR) fclean

re: fclean all


# --- 1 토큰화 ---
# 1. EOF인지?

# 2 이전 캐릭터가 operator의 일부가 될 가능성이 있고, 현재 캐릭터가
# 따옴표도 아니고, 이전 operator에 붙여지면 그 두개를 합친다.

# 안함 3 이전 캐릭터가 operator의 일부가 될 가능성이 있고,
# 현재 캐릭터가 그 뒤에 붙여지지 않으면, 구분한다.

# 4. 따옴표이면, 따옴표 나올때까지 한 덩어리. (후처리 부분을 위해서 메모를 해둬야댐)

# 5. $이면, 캐릭터 알파벳 아닌거 나올때까지 $의 일부로 처리 5

# 6. 현재 문자가 oerator의 가능성이 있으면, 토큰 하나로 구분이 된다.
# 다음 문자는 현재 문자의 operator에 합쳐질 수 있다. 6

# 7. 현재 문자가 공백이면, 무조건 구분해주고 현재 문자(블랭크) 삭제. 7

# 8. 현재 문자가 일반 char이고, 앞에 문자와 연결되면 그 두개 합쳐라. 8

# 9. 현재 문자는 char 문자열의 시작 문자가 된다. 9


# --- 2 후처리 ---
# ERROR 명세: e_error 토큰이 들어있는 노드를 방문할 시, 
# 그 node의 str를 에러 메시지로 전해준다.

# 1. here_doc(<<) 처리 -> 에러 처리(<< > or <<)
# 다음 노드가 NULL이면 error
# 다음 노드가 공백인데, 공백 다음 노드가 NULL이면 error
# 공백 있으면 제거 후, 공백 다음 노드와 현재 노드를 이어줌
# 다음 노드가 오퍼레이터면 error
# here_doc 시작 -> /tmp/here_doc에 해석된 내용을 해석 저장
# read_in2 토큰을 read_in으로, LIMITER 노드의 토근을 string으로 변경

# 2. dollar($) 처리
# 토큰을 string을 변경
# 그냥 $ 하나면 넘어가기
# $?의 경우 g_exit_code로 변경
# 있는 환경변수의 경우 해석한 문자열로 변경
# 없는 환경변수의 경우 빈 문자열로 변경

# 3. double quote("") 처리
# single quote 일 때 따로 하는게 없으므로 토큰을 string으로 변경

# 4. double quote("") 처리
# 문자열 안에 해석할 내용이 있다면 싹다 해석
# 토큰을 string을 변경

# 5. redirection 처리(<, >, >>) -> 에러 처리(< > or >>)
# 다음 노드가 NULL이면 error
# 다음 노드가 공백인데, 공백 다음 노드가 NULL이면 error
# 공백 있으면 제거 후, 공백 다음 노드와 현재 노드를 이어줌
# 다음 노드가 오퍼레이터면 error

# 6. string(그냥 문자열) 처리
# 맨 처음 문자열이 무조건 function임, 뒤에껀 다 argument
# 지금 문자열인데 다음도 문자열이면 병합
# access() 되는가? (그냥 넣기)
# path 붙여가면서 access()

# 7. 에러가 있었다면 break -> g_exit_code = 258
# 여기서 나오는 에러(오퍼레이터 뒤에 오퍼레이터, redirection 뒤에 아무것도 없음)의 
# 경우 이후에 명령들을 실행 안시키기 때문에 break 해줌


# --- 3 리다이랙션 ---
# 1. <(input) 처리 -> 맨 마지막 <의 fd만 기억한다.
# 없거나 권한이 없는 파일은 read_error 처리

# 2. >, >>(output) 처리 -> 맨 마지막 > or >> 의 fd만 기억한다.
# 없거나 권한이 없는 파일은 <과 마찬가지로 read_error 처리

# 3. read_error가 있었다면 -> g_exit_code = 1


# --- 4. 실행 ---
# single 커맨드가 아니면 즉 파이프가 있는 경우,
# cd, export, unset 같은 상태가 바뀌는 명령들이 동작을 안함.

# 함수 인자를 잘못 써서 usage: ~a 나오는 경우 -> g_exit_code = 1
# 없는 명령어의 경우 -> g_exit_code = 127

# 1. echo(with option -n)
# error: 에러 나는 경우가 없음
# -n 인자가 있는 경우 마지막 띄어쓰기 안 넣어주기
# 문자열 사이에 공백 잔뜩있어도 아무 상관 없음 -> 무조건 한 칸씩 띄어쓰기

# 2. cd(with only a relative or absolute path)
# error: 에러 나는 경우가 없음
# error: 인자가 2개 이상 있는 경우 -> 뒤에 꺼 무시함
# cd -> home 경로로
# 상대 경로 -> cd ../test
# 절대 경로 -> cd ~/test
# PWD(현재 경로), OLDPWD(이전 경로)가 담긴 환경 변수가 있기 때문에
# cd 실행 시 수정해줘야 함.

# 3. pwd(with no options)
# error: 에러 나는 경우가 없음
# 현재 디렉토리 경로 출력하기 -> getcwd(buf, bufsize) 사용

# 4. export(with no options)
# error: 에러 나는 경우가 없음
# env와 다르게 key=value(USER=jinhokim)와 같이 = 으로 매칭이
# 되는 것들 뿐만 아니라 안되는 것도 출력함
# key(export a), key=(export a=)
# = 없는 cp_envp[i]는 출력 안하기
# 정렬해서 출력하기

# 5. unset(with no options)
# error: 에러 나는 경우가 없음
# 있는 환경 변수만 cp_envp 에서 삭제하기

# 6. env(with no options or arguments)
# error: 인자가 있는 경우 -> g_exit_code = 1
# env는 key=value(USER=jinhokim)와 같이 = 으로 매칭이 되는 것만 출력함
# = 없는 cp_envp[i]는 출력 안하기

# 7. exit(with no options)
# error: 인자가 2개 이상인 경우 -> g_exit_code = 1
# error: 인자가 숫자가 아닌 경우 -> g_exit_code = 255
# error 아닌  경우 -> cmd_arr[1]로 exit 해줌


# --- 5. 시그널 ---
# 입력 아무 것도 없을 때
# cntl-c -> 새 minishell$ 출력
# cntl-\ -> 신호 무시
# cntl-d -> 새 minishell$ 출력

# 입력이 들어간 상태일 때
# cntl-c -> 새 minishell$ 출력, read_buffer 삭제
# cntl-\ -> 신호 무시
# cntl-d -> 신호 무시

# 실행할 때
# cntl-c -> exit, 새 minishell$ 출력, read_buffer 삭제
# cntl-\ -> exit, 새 minishell$ 출력, read_buffer 삭제
# cntl-d -> exit, 새 minishell$ 출력, read_buffer 삭제