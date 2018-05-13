// <Qing Cheng>
///<: October 20 2017>
//program:
// carwash.cc: implementation of the car wash simulator
//#include <cstdlib> // for c++0x
//#include <time>  // for c++0x
#include <random>  // for c++11
#include <queue>
#include <list>
#include "customer.h"
#include "washevent.h"
//#define RAND1 double(rand()) / RAND_MAX


bool read_debug_option();

int main()
{
    double avg_num=0;
    double time_record=0;
    double total_wait=0;
    int wait_customer=0;
    int queuenumber=0;
    int index=0;
    int i = 0;
    
    // average time interval between two consecutive arrivals
	double ave_interarrival_time;

    // average service time for each customer
	double ave_service_time;

    // total simulation time
	double total_simulation_time;

    // debug options
	bool debug_opt1, debug_opt2;

	//----------------------------------------------------------------------
	//get user inputs
	cout << "Input the average time interval of two consecutive intervals: ";
	cin >> ave_interarrival_time;

	cout << "Input the average service time: ";
	cin >> ave_service_time;

	cout << "Input the simulation time: ";
	cin >> total_simulation_time;

	// The following can be comment out during debugging
	// total simulation time should be at least 10,000 * ave_interarrival_time
	if (total_simulation_time < 10000 * ave_interarrival_time)
	{
		cout << "Error: total simulation time should be greater than " << ave_interarrival_time * 10000 << endl;
		return 1;
	}

	cout << "Debugging option:" << "\n";
    cout << "- Print items in queue whenever there is a change in queue? (y/n): ";
	debug_opt1 = read_debug_option();
	cout << "- Print events when there is an arrival or departure? (y/n): ";
	debug_opt2 = read_debug_option();

	//----------------------------------------------------------------
	// create a queue of customers coming to the carwash
    queue <customer*> line;

	//create a list of events
	list <washevent*> event_list;

	//initialization randon number generator and distributions
	random_device rd;
	default_random_engine gen(rd());
	uniform_real_distribution<double> arrival_dis(0.0, 2.0*ave_interarrival_time);
	uniform_real_distribution<double> service_dis(0.0, 2.0*ave_service_time);
	
    
    washevent *event =new washevent;
    event->set_customerid(1);
    event->set_type(arrival);
    event->set_time(arrival_dis(gen));
    event_list.push_back(event);
    
    
	
    washevent *end = new washevent;
    end->set_type(end_of_simulation);
    
    
    
	washevent *next_event =new washevent;
	do
    {

	    // retrieve the next event from the event list
	    next_event = event_list.front();

        event_list.pop_front();

	    switch  (next_event->get_type())
	    {
            case arrival:
            {
                customer  new_c;
                washevent event1;
                queuenumber=0;
                if(line.empty() == 1)
                {
                    event1.set_type(departure);
                    event1.set_time(service_dis(gen)+next_event->get_time());
                    event1.set_customerid(next_event->get_customerid()+i);
                    event_list.push_back(&event1);
                    new_c.set_id(next_event->get_customerid());
                    new_c.set_arrival(next_event->get_time());
                    new_c.set_departure(event1.get_time());
                    line.push(&new_c);
                    
                }
                else{
                    customer *new_a = new customer;
                    new_a->set_id(next_event->get_customerid());
                    new_a->set_arrival(next_event->get_time());
                    new_a->set_departure(0);
                    line.push(new_a);
                    
                    
                }
                
            
                
                
                
                
                if(debug_opt1 == true){
                next_event->print_info();
                }
                if(debug_opt2 == true)
                {
                cout<<"[debug] Queue at time "<<next_event->get_time()<<"(from front to rear): ";
                queue<customer*> test;
                
                test = line;
                for(unsigned int i=0; i<line.size(); i++){
                    cout<<"C"<<test.front()->get_id()<<" ";
                    queuenumber +=1;
                    test.pop();
                    
                }
                cout<<"\n";
                }
               
                
                
                //time_record = next_event->get_time();
                washevent *arrvial1= new washevent;
                double atime;
                atime = next_event->get_time()+arrival_dis(gen);
                if(atime >total_simulation_time){
                    event_list.front()->set_type(end_of_simulation);
                    break;
                }
                
                if(index != 0){
                   avg_num +=((next_event->get_time() - time_record) * queuenumber) / total_simulation_time;
                }
                time_record = next_event->get_time();

                
                arrvial1->set_type(arrival);
                arrvial1->set_customerid(next_event->get_customerid()+1);
                arrvial1->set_time(atime);
                event_list.push_back(arrvial1);
               
                // if the line is empty, update departure time
                // create a departure event and push into the event list
                
				// push the customer into the customer line

                // create a new arrival event and push into the event list

				// sort the event list in chronological order
				event_list.sort(comp_time);
                break;
            }

            case departure:
            {// TODO: add your code below ...
                // pop the front customer from the line
                queuenumber=0;
                line.pop();
                if(line.empty() != 1){
                    washevent *event2 =new washevent;
                    event2->set_type(departure);
                    event2->set_time(next_event->get_time()+service_dis(gen));
                    event2->set_customerid(next_event->get_customerid()+1);
                    event_list.push_back(event2);
                    line.front()->set_departure(event2->get_time());
                    
                    
                    
                }
                // if the line is not empty, update the departure time of the next customer
				// create a new departure event and push into the event list
                
				// sort the event list in chronological or
				event_list.sort(comp_time);
                if(debug_opt1 == true){
                    next_event->print_info();
                }
                if(debug_opt2 == true)
                {
                    cout<<"[debug] Queue at time "<<next_event->get_time()<<"(from front to rear): ";
                    queue<customer*> test;
                    
                    test = line;
                    for(unsigned int i=0; i<line.size(); i++){
                        cout<<"C"<<test.front()->get_id()<<" ";
                        
                        test.pop();
                        
                    }
                    cout<<"\n";
                }

                avg_num +=((next_event->get_time() - time_record) * queuenumber) / total_simulation_time;
                time_record = next_event->get_time();
                index++;
                if(line.size() != 0){
                total_wait += next_event->get_time()-line.front()->get_arrival();
                wait_customer++;
                }
                
                break;
            }

            case end_of_simulation:
            {
                next_event->print_info();
                cout<<"The average number of customers in the queue is "<<avg_num<<endl;
                cout<<"The average waiting time for a customer is "<<total_wait/wait_customer<<endl;
                break;
            }

            default:
            {
                cout << "Error: incorrect event type." << endl;
            }
        }

	} while ( !event_list.empty() );

	return 0;
}

bool read_debug_option() 
{
	char input;
	cin >> input;
	if ( input == 'Y' || input == 'y') return true;
	if ( input == 'N' || input == 'n') return false;
	
	cout << "Error: incorrect input option!" << endl;
	exit(1);
}