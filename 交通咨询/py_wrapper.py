from ctypes import *

lib_traffic = CDLL('./libtraffic.so')

#lib_traffic.print_interface_header()
#lib_traffic.test_user_input_from_keyboard()

#lib_traffic.test_print_ticket_info()
#lib_traffic.test_insert_new_ticket_info()
#lib_traffic.test_delete_ticket_info()
#lib_traffic.test_find_route()
lib_traffic.interface()
