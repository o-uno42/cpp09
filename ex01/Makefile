CPP = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98

TARGET = RPN

SRCS = main.cpp RPN.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CPP) $(CPPFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

fclean:	clean
	rm -rf $(NAME)

re: clean all
