# Converting Ascii to Binary
+ Ascii short for American Standard Code for Information Interexchange, ASCII is a standard that assigns letters, numbers, and other characters in the 256 slots available in the 8-bit code. The ASCII decimal (Dec) number is created from binary, which is the language of all computers. As shown in the table below, the lowercase "h" character (Char) has a decimal value of 104, which is "01101000" in binary.
+ The way two programs can communicate via signals - more precosely `SIGUSR1` and `SIGUSR2` - is to make them represent a binary value each. in this case we consider that `SIGUSR1` represent 0 in binary, and `SIGUSR2` represent 1. So when we send `SIGUSR1` signal we sending 0 to `server` (the program who receives the signals), and by sending `SIGUSR2` signal we are sending 1.
+ The first step here is to send all the 8 bits, just by using the signals `SIGUSR1` and `SIGUSR2` - This means that server will need to receive 8 signals from `client` (The program who responsible about sending signals) for every ASCII character.
> The character H is represented by the number 72 in the ASCII table. in binary 01001000
+ The big question here is how to get the character's bits one by one.!
We get them by using Bitwise Operators. \ More precisely << and &:
> The LEFT SHIFT (<<) operator moves the bits to the left, discards the far left bit, and assigns the rightmost bit a value of 0. 
+ > 00000001 << 1 = 00000010 [1 << 1 = 2] 
+ > 00000001 << 2 = 00000100 [1 << 2 = 4]

> The AND (&) compares two bits and generates a results of 1 if both bits are 1. otherwise it returns 0.
+ > 01001000 & 10000000 = 00000000 [72 & 128 = 0]
+ > 01001000 << 1 = 10010000 [72 << 1 = 144]
+ > 10010000 & 10000000 = 10000000 [144 & 128 = 128]
+ By using the number 128 we get a binary number that has only 1 at the left of the bits, so need to send the first bit from the left of 8 of the character, by using the left shift operator and the betwise operator '&', like this : compare the left bit with 1, if the current bit is 0, then 1 & 0 = 0, if the current bit is 1 then 1 & 1 = 0, that's and like so until we finish all the bits by shifting them to the left until we finish 8 bits.
##### Example
+ This example shows how the program works, if the current bit is 0 the function `ft_bin` will prints that bit, if the bit is 1 she will print it.

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:07:50 by ahammout          #+#    #+#             */
/*   Updated: 2022/03/04 19:11:28 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"stdio.h"

static  void    ft_bin(char c)
{
    int bit;

    bit =0;
    printf("%c : ", c);
    while (bit < 8)
    {
        if (c & 128)
            printf("1");
        else
            printf("0");
        c = c << 1;
        bit ++;
    }
}

static  void    ft_sender_char(char *str)
{
    int i;

    i = 0;
    printf("The string : %s\n", str);
    while (str[i])
    {
        ft_bin(str[i]);
        i++;
        printf("\n");
    }
}


int main(int argc, char **argv)
{
	ft_checker_sender(argv[1]);
	return(0);
}

```
input : "ahammout"
```
Output :
The string : ahammout
a : 01100001
h : 01101000
a : 01100001
m : 01101101
m : 01101101
o : 01101111
u : 01110101
t : 01110100
```
## Real exemple from the code : 
#### Client.c :
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:48:11 by ahammout          #+#    #+#             */
/*   Updated: 2022/03/15 17:40:56 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ft_sender_bin(int pid, char c)
{
	int	bit;
	int	n;

	bit = 0;
	while (bit < 8)
	{
		if (c & 128)
			n = kill(pid, SIGUSR2);
		else
			n = kill(pid, SIGUSR1);
		if (n == -1)
		{
			ft_printf("[ PID ] : bad process ID");
			exit(EXIT_FAILURE);
		}
		c = c << 1;
		bit ++;
		usleep(700);
	}
}

static void	ft_sender_char(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_sender_bin(pid, str[i]);
		i++;
	}
}
```

# Converting Binary to ascii
+ The `client` sends the signal to the `server`, this signal can be a 0 if SIGUSR1, and can be 1 if the signal is SIGUSR2, So to receive bits we will do the same operation as the client receiving all the 8 bits by storing every bits inside a variable each time the server got a signal; the quetion here is how to store all the received bits, for that we can use the betwise operator 'or' `|` This operator, is diffrent from `&` operator because `|` can give 1 only if both operands are 1.  `Ex1 : 10000000 | 10001000 = 10000000 in this case 128 | 136 = 128`.  `Ex0 : 00010000 | 10000000 = 00000000 in this case 16 | 128 = 0`.
### Example : receiving the character "H" from the client, ASCII "72"
```c
character "H " : 72 = 01001000
variable c : 0 = 00000000
 received SIGUSR1 : c |= 00000000 = 00000000  //bit 1
c <<= 1 ; c = 00000000
 received SIGUSR2 : c |= 00000001 = 00000001  //bit 2
c <<= 1 ; c = 00000010
 received SIGUSR1 : c |= 00000000 = 00000010 //bit 3
c <<= 1 ; c = 00000100
 received SIGUSR1 : c |= 00000000 = 00000100 //bit 4
c <<= 1 ; c = 00001000
 received SIGUSR2 : c |= 00000001 = 00001001 //bit 5
c <<= 1 ; c = 00010010
 received SIGUSR1 : c |= 00000000 = 00010010 //bit 6
c <<= 1 ; c = 00100100
 received SIGUSR1 : c |= 00000000 = 00100100 // bit 7
c <<= 1 ; c = 01001000
 received SIGUSR1 : c |= 00000000 = 01001000 // bit 8
```
## Real example from the code : 
#### server.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:48:32 by ahammout          #+#    #+#             */
/*   Updated: 2022/03/15 20:06:53 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>

static void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static int	bit;
	static int	c;

	(void)context;

	c <<= 1;
	c = c | (sig == SIGUSR2);
	bit ++;
	if (bit == 8)
	{
		printf("%c", c);
		c = 0;
		bit = 0;
	}
}
```
