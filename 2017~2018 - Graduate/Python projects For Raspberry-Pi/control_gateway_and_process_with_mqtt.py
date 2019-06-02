# 라이브러리 포함
import time
import sys

# 경로 추가
sys.path.append("./control_gateway_and_process_with_mqtt_files")
# 위 경로에 있는 파일 중 끌어다 쓸 파일을 import
import thread_controller
from file_printer import make_file_name_with_date_and_ext, ADMIN


#output_file_name = make_file_name_with_date_and_ext(ADMIN)
#output_file = open(output_file_name, "w")
#default_stdout, sys.stdout = sys.stdout, output_file


thread_controller.run_all_threads()

#gpio_controller.RST_TO_LOW()
#gateway_controller.start_gateway_repair_timer()
#while True:
#	gateway_controller.run_gateway()
#gateway_controller.run_gateway()