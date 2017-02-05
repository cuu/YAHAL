/*
 * stdin_interface.h
 *
 *  Created on: 13.03.2016
 *      Author: Andreas Terstegge
 */

#ifndef _STDIN_INTERFACE_H_
#define _STDIN_INTERFACE_H_

class stdin_interface {
  public:
    virtual ~stdin_interface() { }
	virtual char getc() = 0;
};

#endif // _STDIN_INTERFACE_H_
