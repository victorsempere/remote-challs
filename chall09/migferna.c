#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int parser(int seconds, int d)
{
	int min;

	min = seconds/d;
	return min;
}

char *generate_output(int years, int months, int days, int hours, int minutes, int seconds)
{
	char *format;

	char *minutes_count;
	char *seconds_count;
	char *hours_count;
	char *years_count;
	char *months_count;
	char *days_count;

	if (!(format = malloc(100)))
		return NULL;
	minutes_count = minutes > 1 ? "minutes" : "minute";
	seconds_count = seconds > 1 ? "seconds" : "second";
	hours_count = hours > 1 ? "hours" : "hour";
	years_count = years > 1 ? "years" : "year";
	months_count = months > 1 ? "months" : "month";
	days_count = days > 1 ? "days" : "day";

	sprintf(format, "%d %s, %d %s, %d %s, %d %s, %d %s, %d %s", years, years_count, months,months_count, days, days_count, hours, hours_count, minutes, minutes_count, seconds, seconds_count);
	return (format);
}

char *parser_format(char *s)
{
	char *out;

	int seconds = atoi(s);
	int minutes = 0;
	int hours = 0;
	int days = 0;
	int months = 0;
	int years = 0;

	if (seconds == 0) {
		out = "now";
		return out;
	}
	if (seconds > 60)
	{
		minutes = parser(seconds, 60);
		seconds = seconds % 60;
	}
	if (minutes > 60)
	{
		hours = parser(minutes, 60);
		minutes = minutes % 60;
	}
	if (hours > 24)
	{
		days = parser(hours, 24);
		hours = hours % 24;
	}
	if (days > 31)
	{
		months = parser(days, 31);
		days = days % 31;
	}
	if (months > 12)
	{
		years = parser(days, 12);
		days = days % 12;
	}
	
	out = generate_output(years, months, days, hours, minutes, seconds);
	return (out);
}

int	is_valid(char *seconds)
{
	char *ptr = strtok(strdup(seconds), " ");
	int num_digits = 0;
	while (ptr)
	{
		if (isdigit(*ptr))
		{
			num_digits++;
			ptr = strtok(NULL, " ");
		}
		else if((*ptr == '+' || *ptr == '-') && !isdigit(*(ptr + 1)))
			ptr = strtok(NULL, " ");
		else
			return 0;
	}
	if (num_digits > 1)
		return 0;
	return (1);
}

char *ft_format_duration(char *seconds)
{
	char *out;
	if (*seconds && is_valid(seconds))
		out = parser_format(seconds);
	else
		out = "Invalid input.";
	return out;
}

int main()
{
	printf("%s\n", ft_format_duration("62"));
	printf("%s\n", ft_format_duration("3662"));
	printf("%s\n", ft_format_duration("0"));
	printf("%s\n", ft_format_duration("LOL42LOL"));
	printf("%s\n", ft_format_duration(""));
	printf("%s\n", ft_format_duration("2175984000"));
	printf("%s\n", ft_format_duration("   42"));
	printf("%s\n", ft_format_duration(" +  42"));
	printf("%s\n", ft_format_duration("   42 1"));
	printf("%s\n", ft_format_duration("42 1"));
	printf("%s\n", ft_format_duration("42   "));
	printf("%s\n", ft_format_duration("+42"));
	printf("%s\n", ft_format_duration("-42"));
	printf("%s\n", ft_format_duration("0042"));
	printf("%s\n", ft_format_duration("0 42"));
	return (0);
}
