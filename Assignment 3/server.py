################################################################################
#	CSC 485A - Assignment 3
#	@author    Richard B. Wagner
#	@author    MacKay McGillivray
#	@author    Jon G. Bowen
#	@version   0.1
#	@date      2015-07-10
#	@copyright GNU Public License.
################################################################################

# Dependencies
################################################################################

try:
	import threading as _threading
except ImportError:
	import dummy_threading as _threading
import socketserver
import time
from urllib.parse import urlparse, parse_qs
import queue


# Global Variables
################################################################################

# port of the server
PORT = 8080;

# global thread safe queue to pipe requests into the MAPE-K loop
request_queue = [];


job_queue = {}

symptom_names = ["duplicate requests detected","malicious user detected"]
current_symptoms = []

# Utility Functions
################################################################################

def dispatcher(request, args):
	if(request=='addJob'):
		print("dispatcher: id[" +str(args['id'][0])+ "]")
		job_queue[str(args['id'][0])] = {'name':args['name'][0], 'id':args['id'][0], 'runtime':args['runtime'][0], 'priority':args['priority'][0], 'start':time.time()};
		#print("dispatcher: "+str(job_queue[str(args['id'][0])]))
	#elif(request=='modifyJob'):
	#	modifyJob(name, id, runtime, priority)
	#elif(request=='removeJob'):
	#	removeJob(id)

# Classes
################################################################################

class MyTCPHandler(socketserver.BaseRequestHandler):
	
	def handle(self):
		while(True):
			self.data = self.request.recv(1024)
			if not self.data:
				print('DISCONNECTED')
				break
			
			# Do data decode and format
			tmp_data = self.data.decode('utf-8').split('\r\n')
			_data = {}
			for i in range(0, len(tmp_data)):
				tmp = tmp_data[i].split();
				if(len(tmp)>1):
					_data[tmp[0]] = tmp[1:]
			url = urlparse('http://' + _data['Host:'][0] + _data['GET'][0])
			
			
			if(len(url[2])>1 and url[2][1:] == 'status'):
				print("Sending Status");
				content = "<html><head><title>Status</title></head><body><h1>Status</h1>"
				for key in job_queue:
					print("TEST")
					content += str(job_queue[key]) + "<br \>"
					print ("STATUS" + job_queue[key])
				
				content += "</body></html>"
				
			elif(len(url[2])>1 and url[2][1:] != 'favicon.ico' ):
				request_queue.append([url[2][1:], parse_qs(url[4],keep_blank_values=True)])
				content ="<html><body><h1>Your Request Has Been Recieved</h1></body></html>"
			
			
			
			header = "HTTP/1.1 200 OK\nContent-length: " + str(len(content)) + "\nContent-Type: text/html\n\n"
			
			self.request.sendall(str(header+content).encode('utf-8'))
			
			
# Main
################################################################################

if __name__ == "__main__":
	server = socketserver.TCPServer(('localhost', PORT), MyTCPHandler)
	
	# put actual listener on different thread for asynchronous job retrieval
	_threading.Thread(target=server.serve_forever).start()
	
	# MAPE-K loop
	while(True):
		
		# pause loop
		time.sleep(0.5)
		
		# Monitor
		########################################################################
		
		# if request_queue is not empty
		if(request_queue):
			# fetch request from queue
			request = request_queue.pop(0)
		else:
			request = None
		
		# Analyze/Plan
		########################################################################
		
		# if a job has gone past its max runtime, scheduale it for removal
		r_queue = []
		for i in job_queue:
			if(float(job_queue[i]['runtime']) > time.time() - job_queue[i]['start']):
				r_queue.append(job_queue[i])
				
		# if there is "room" in the execution list
		room = (len(job_queue)<=3)
			
		
		
		# Execute
		#job_queue.append()
	
		########################################################################
		
		# for
		#while r_queue:
		#	del job_queue[r_queue.pop()['id']]
		
		if(request and room):
			dispatcher(request[0], request[1])
			print("Updated: "+str(len(job_queue))+"  |"+str(job_queue))


def init():
	init_server()
	init_autonomic_manager()

def init_server():
	return None

def init_autonomic_manager():
	init_knowledge_database();

def init_knowledge_database():
	init_event_log();
	init_symptoms_database();

def init_event_log():

def init_symptoms_database():
	# Enumerate symptoms
	return None

def symptom_check(symptom_name):
	symptom = 0
	if (symptom_name == "duplicate requests detected"):
		#execute symptom engine for "duplicate requests detected" symptom
	elif (symptom_name == "malicious user detected"):
		#execute symptom engine for "malicious user detected" symptom
	#etc.
	return symptom

def autonomic_manager_control_cycle():
	monitor()
	analyze()
	plan()
	execute()

def managed_element_control_cycle():
	return None

def retrieve_state_from_managability_endpoint():
	#lazily execute managed element cycle directly before retrieving its state
	returned_event = managed_element_control_cycle()
	return returned_event

def monitor():
	#event_current = retrieve_state_from_managability_endpoint()
	#write_event_to_event_log_buffer(event)

	# if request_queue is not empty
	if(request_queue):
		# fetch request from queue
		request = request_queue.pop(0)
	else:
		request = None

	#check for new symptoms
	for symptom_name in symptom_names:
		symptom_check(symptom_name)
	return None

def write_event_to_event_log_buffer(event):
	return None

def flush_event_log_buffer():
	return None

def analyze():
	# if a job has gone past its max runtime, scheduale it for removal
	r_queue = []
	for i in job_queue:
		if(float(job_queue[i]['runtime']) > time.time() - job_queue[i]['start']):
			r_queue.append(job_queue[i])
			
	# if there is "room" in the execution list
	room = (len(job_queue)<=3)

	# Execute
	#job_queue.append()

	########################################################################
	
	# for
	#while r_queue:
	#	del job_queue[r_queue.pop()['id']]
	
	if(request and room):
		dispatcher(request[0], request[1])
		print("Updated: "+str(len(job_queue))+"  |"+str(job_queue))

def plan():
	return None

def execute():
	return None
