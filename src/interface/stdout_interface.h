/*
 * stdout_interface.h
 *
 *  Created on: 13.03.2016
 *      Author: Andreas Terstegge
 */

#ifndef _STDOUT_INTERFACE_H_
#define _STDOUT_INTERFACE_H_

class stdout_interface {
  public:
	virtual void putc(char c) = 0;
};

#endif // _STDOUT_INTERFACE_H_
