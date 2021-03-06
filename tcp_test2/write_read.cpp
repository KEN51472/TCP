#include "unp.h"

ssize_t                    /* read "n" bytes from a descriptor. */
readn(int fd, void *vptr, size_t n)
{
    size_t     nleft;
    ssize_t    nread;
    char       *ptr;
    
    ptr = (char *)vptr;
    nleft = n;
    while(nleft > 0)
    {
        if((nread = read(fd, ptr, nleft)) < 0)
        {
            if(errno == EINTR)
                nread = 0;    /* and call read() again */
            else
                return(-1);
        }
        else if(nread == 0)
            break;            /* EOF */

        nleft -= nread;
        ptr += nread;
    }
    return(n - nleft);            /* return >= 0 */
}

ssize_t                    /* write n bytes to a descriptor */
writen(int fd, const void *vptr, size_t n)
{
    size_t         nleft;
    ssize_t        nwritten;
    const char    *ptr;

    ptr = (char *)vptr;
    nleft = n;
    while(nleft > 0)
    {
        if((nwritten = write(fd, ptr, nleft)) <= 0)
        {
            if(nwritten < 0 && errno == EINTR)
                nwritten = 0;    /* and call write again */
            else
                return(-1);    /* error */
        }
        
        nleft -= nwritten;
        ptr += nwritten;
    }
    return(n - nwritten);
}

ssize_t
readline(int fd, void *vptr, size_t maxlen)
{
    ssize_t        n, rc;
    char           c, *ptr;
    
    ptr = (char *)vptr;
    for(n = 1; n < maxlen; n++)
    {
    again:
        if((rc = read(fd, &c, 1)) == 1)
        {
            *ptr++ = c;
            if(c == '\n')
                break;    /* newline is stored, like fgets() */
        }
        else if(rc == 0)
        {
            *ptr = 0;
            return(n - 1);    /* EOF, n - 1 bytes were read */
        }
        else
        {
            if(errno == EINTR)
                goto again;
            return(-1);    /* error, errno set by read() */
        }
    }

    *ptr = 0;    /* null terminate like fgets() */
    return(n);
}