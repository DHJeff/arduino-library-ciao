/*
****************************************************************************
* Copyright (c) 2015 Arduino srl. All right reserved.
*
* File : CiaoData.h
* Date : 2015/07/03
* Revision : 0.0.1 $
*
****************************************************************************

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include <Arduino.h>

#define ID_ERROR		String(-1)
#define ID_EMPTY		String(0)
#define ID_READY		String(1)
#define END_TX_CHAR 	(char)4
#define DATA_SPLIT_CHAR (char)30
#define ID_SIZE_TX		25

class CiaoData {
	public:
		
		String get(int index){
			return msg_split[index];
		}
		
		void split_command(String command, String split){		//fuction to split the digital/analog command (ex: digital/13/1)
			if(command.indexOf(split) != -1){		//if command is empty don't running the split
				int statusIndex = command.indexOf(split);
				int messIndex = command.indexOf(split, statusIndex+1);
				msg_split[0] = command.substring(0, statusIndex);
				msg_split[1] = command.substring(statusIndex+1, messIndex);
				if(messIndex != -1)
					msg_split[2] = command.substring(messIndex+1);
				else
					msg_split[2]="-1";
			}
		}
		
		void parseMessage(String command){
			int statusIndex = command.indexOf(DATA_SPLIT_CHAR);
			msg_split[1] = command.substring(0, statusIndex);
			msg_split[2] = command.substring(statusIndex+1);
		}
  
		bool isError(){		//check for an error in data received
			if(get(0) == ID_ERROR)
				return true;
			else
				return false;			
		}
		
		bool isEmpty(){		//check if data received is empty
			if(get(0) == ID_EMPTY)
				return true;
			else
				return false;	
		}
		
	public:
		String msg_split[3];
		
};


