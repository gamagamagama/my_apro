int print_str(const char *str)
{
    int i = 0;
    if(str == NULL){
        write(1, "(null)", 6);
        return(6);
    }
    while(str[i])
    {
        i++;
    }
    write(1, str, i);
    return(i);
}

int print_nmb(long num, int base)
{
    int counter = 0;
    char c;
    char *numbers = "0123456789abcdef";
    if(base < 2 || base > 16)
        return 0;
    if(num < 0 && base == 10)
    {
        counter += write(1, "-", 1);
        num = -num;
    }
    if(num >= base)
    {
        counter += print_nmb(num / base, base);
        counter += print_nmb(num % base, base);
    }
    else
    {
        c = numbers[num];
        counter += write(1, &c, 1);
    }
    return counter;
}

int print_smth(const char *input, va_list arg)
{
    int counter = 0;
    if(*input == 's')
        counter += print_str(va_arg(arg, const char *));
    else if(*input == 'd')
        counter += print_nmb(va_arg(arg, int), 10);
    else if(*input == 'x')
        counter += print_nmb(va_arg(arg, unsigned long), 16);
    return(counter);
}

int print_in(char c)
{
    int counter = 0;
    counter += write(1, &c, 1);
    return(counter);
}

int mprintf (const char *input, ...)
{
    va_list arg;
    int counter = 0;

    int i = 0;
    va_start(arg, input);

    while(input[i])
    {
        if(input[i] == '%')
            counter += print_smth(&input[++i], arg);
        else
            counter += print_in(input[i]);
        i++;
    }
    va_end(arg);
    return(counter);
}

int main ()
{   
    char str[5] = "helll";
    int c = 42;
    //unsigned long = 
    int a = printf("A:%s HElllo %x World%d\n", str, c, c);
    int b = mprintf("B:%s HElllo %x World%d\n", str, c, c);

    printf("a:%d\nb:%d\n", a , b);
}
