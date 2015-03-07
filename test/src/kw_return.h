#if !defined KW_RETURN_H
#define      KW_RETURN_H

/* This is some return() in a comment */

#define RETURN( _return ) do { if ( _return < 0 ) { return 0; } } while( 0 )

extern int err;

inline int x_return( int y_return )
{
    RETURN( y_return );

    if( y_return > 100 )
    {
        return 1;
    } else if( y_return > 50 )
    {
	return 2;
    } else
    {
	return 3;
    }
}

#endif
