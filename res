Creating the system ---
--- At station: 
(re)schedule job: from 0 to 1

  STATION:
    id:             0
    clients inside: 4
    arrivals:       4
    departures:     0
Generated the event:
(re)schedule job: from 0 to 1

  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 0.000000
    leaving at: 0.000000
    permanence: 0.000000
Generated the event:
(re)schedule job: from 0 to 1

  EVENT:
    name:       J1
    from:       0
    to:         1
    created:    0.000000
    arrived at: 0.000000
    leaving at: 4.670026
    permanence: 4.670026
Generated the event:
(re)schedule job: from 0 to 1

  EVENT:
    name:       J2
    from:       0
    to:         1
    created:    0.000000
    arrived at: 0.000000
    leaving at: 29.913183
    permanence: 29.913183
Generated the event:

  EVENT:
    name:       J3
    from:       0
    to:         1
    created:    0.000000
    arrived at: 0.000000
    leaving at: 14.834469
    permanence: 14.834469
--- At station: 

  STATION:
    id:             1
    clients inside: 0
    arrivals:       0
    departures:     0
--- At station: 

  STATION:
    id:             2
    clients inside: 0
    arrivals:       0
    departures:     0
--- System created
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 0.000000
    leaving at: 0.000000
    permanence: 0.000000
***nothing to dequeue:
***Station 1 here: (re)schedule job: from 1 to 2
***job rerouted as:

  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 0.000000
    leaving at: 3.576837
    permanence: 3.576837
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 0.000000
    leaving at: 3.576837
    permanence: 3.576837
***nothing to dequeue:
***Station 2 here: *****new service assigned: 7.401121
*****job sliced:
***job sent back as:

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 0.000000
    leaving at: 6.576837
    permanence: 4.401121
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J1
    from:       0
    to:         1
    created:    0.000000
    arrived at: 0.000000
    leaving at: 4.670026
    permanence: 4.670026
***nothing to dequeue:
***Station 1 here: (re)schedule job: from 1 to 2
***job rerouted as:

  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 9.242805
    permanence: 4.572779
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 0.000000
    leaving at: 6.576837
    permanence: 4.401121
***nothing to dequeue:
***Station 2 here: *****job sliced:
***job sent back as:

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 0.000000
    leaving at: 9.576837
    permanence: 1.401121
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 9.242805
    permanence: 4.572779
***nothing to dequeue:
***Station 2 here: ***job enqueued

  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 9.242805
    permanence: 4.572779
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 0.000000
    leaving at: 9.576837
    permanence: 1.401121
*****dequeue the event:
*****new service assigned: 16.909059

  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 9.242805
    permanence: 4.572779
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 12.576837
    permanence: 13.909059
***job enqueued

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 0.000000
    leaving at: 9.576837
    permanence: 1.401121
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 12.576837
    permanence: 13.909059
*****dequeue the event:
(re)schedule job: from 2 to 0

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 0.000000
    leaving at: 9.576837
    permanence: 1.401121
*****dequeued job and rerouted as:
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         0
    created:    0.000000
    arrived at: 9.576837
    leaving at: 13.977958
    permanence: 1.401121
***job enqueued

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 12.576837
    permanence: 13.909059
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         0
    created:    0.000000
    arrived at: 9.576837
    leaving at: 13.977958
    permanence: 1.401121
*****dequeue the event:

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 12.576837
    permanence: 13.909059
*****job sliced:
*****dequeued job and sent back as:
***Station 0 here: (re)schedule job: from 0 to 1

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 16.977958
    permanence: 10.909059
***job rerouted as:

  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 13.977958
    leaving at: 21.145091
    permanence: 7.167134
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J3
    from:       0
    to:         1
    created:    0.000000
    arrived at: 0.000000
    leaving at: 14.834469
    permanence: 14.834469
***nothing to dequeue:
***Station 1 here: (re)schedule job: from 1 to 2
***job rerouted as:

  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 14.834469
    leaving at: 17.652893
    permanence: 2.818424
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 16.977958
    permanence: 10.909059
***nothing to dequeue:
***Station 2 here: *****job sliced:
***job sent back as:

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 19.977958
    permanence: 7.909059
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 14.834469
    leaving at: 17.652893
    permanence: 2.818424
***nothing to dequeue:
***Station 2 here: ***job enqueued

  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 14.834469
    leaving at: 17.652893
    permanence: 2.818424
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 19.977958
    permanence: 7.909059
*****dequeue the event:
*****new service assigned: 1.313916
(re)schedule job: from 2 to 0

  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 14.834469
    leaving at: 17.652893
    permanence: 2.818424
*****dequeued job and rerouted as:
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         0
    created:    0.000000
    arrived at: 17.652893
    leaving at: 21.291873
    permanence: 1.313916
***job enqueued

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 19.977958
    permanence: 7.909059
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 13.977958
    leaving at: 21.145091
    permanence: 7.167134
***nothing to dequeue:
***Station 1 here: (re)schedule job: from 1 to 2
***job rerouted as:

  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 21.145091
    leaving at: 33.686134
    permanence: 12.541043
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         0
    created:    0.000000
    arrived at: 17.652893
    leaving at: 21.291873
    permanence: 1.313916
*****dequeue the event:

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 19.977958
    permanence: 7.909059
*****job sliced:
*****dequeued job and sent back as:
***Station 0 here: (re)schedule job: from 0 to 1

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 24.291873
    permanence: 4.909059
***job rerouted as:

  EVENT:
    name:       J3
    from:       0
    to:         1
    created:    0.000000
    arrived at: 21.291873
    leaving at: 31.299904
    permanence: 10.008031
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 24.291873
    permanence: 4.909059
***nothing to dequeue:
***Station 2 here: *****job sliced:
***job sent back as:

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 27.291873
    permanence: 1.909059
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 4.670026
    leaving at: 27.291873
    permanence: 1.909059
***nothing to dequeue:
***Station 2 here: (re)schedule job: from 2 to 0
***job and rerouted as:

  EVENT:
    name:       J1
    from:       2
    to:         0
    created:    0.000000
    arrived at: 27.291873
    leaving at: 29.200932
    permanence: 1.909059
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         0
    created:    0.000000
    arrived at: 27.291873
    leaving at: 29.200932
    permanence: 1.909059
***nothing to dequeue:
***Station 0 here: (re)schedule job: from 0 to 1
***job rerouted as:

  EVENT:
    name:       J1
    from:       0
    to:         1
    created:    0.000000
    arrived at: 29.200932
    leaving at: 33.458612
    permanence: 4.257680
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J2
    from:       0
    to:         1
    created:    0.000000
    arrived at: 0.000000
    leaving at: 29.913183
    permanence: 29.913183
***nothing to dequeue:
***Station 1 here: ***job enqueued
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J3
    from:       0
    to:         1
    created:    0.000000
    arrived at: 21.291873
    leaving at: 31.299904
    permanence: 10.008031
***nothing to dequeue:
***Station 1 here: ***job enqueued
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J1
    from:       0
    to:         1
    created:    0.000000
    arrived at: 29.200932
    leaving at: 33.458612
    permanence: 4.257680
***nothing to dequeue:
***Station 1 here: ***job enqueued
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 21.145091
    leaving at: 33.686134
    permanence: 12.541043
*****BEFORE: dequeue the event:
(re)schedule job: from 1 to 2

  EVENT:
    name:       J2
    from:       0
    to:         1
    created:    0.000000
    arrived at: 0.000000
    leaving at: 29.913183
    permanence: 29.913183
*****dequeued job rerouted as:
***Station 2 here: *****new service assigned: 5.079935

  EVENT:
    name:       J2
    from:       1
    to:         2
    created:    0.000000
    arrived at: 29.913183
    leaving at: 48.474278
    permanence: 14.788144
*****job sliced:
***job sent back as:

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 21.145091
    leaving at: 36.686134
    permanence: 2.079935
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 21.145091
    leaving at: 36.686134
    permanence: 2.079935
***nothing to dequeue:
***Station 2 here: (re)schedule job: from 2 to 0
***job and rerouted as:

  EVENT:
    name:       J0
    from:       2
    to:         0
    created:    0.000000
    arrived at: 36.686134
    leaving at: 38.766069
    permanence: 2.079935
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         0
    created:    0.000000
    arrived at: 36.686134
    leaving at: 38.766069
    permanence: 2.079935
***nothing to dequeue:
***Station 0 here: (re)schedule job: from 0 to 1
***job rerouted as:

  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 38.766069
    leaving at: 39.886999
    permanence: 1.120930
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 38.766069
    leaving at: 39.886999
    permanence: 1.120930
***nothing to dequeue:
***Station 1 here: ***job enqueued
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J2
    from:       1
    to:         2
    created:    0.000000
    arrived at: 29.913183
    leaving at: 48.474278
    permanence: 14.788144
*****BEFORE: dequeue the event:
(re)schedule job: from 1 to 2

  EVENT:
    name:       J3
    from:       0
    to:         1
    created:    0.000000
    arrived at: 21.291873
    leaving at: 31.299904
    permanence: 10.008031
*****dequeued job rerouted as:
***Station 2 here: *****new service assigned: 2.990509
(re)schedule job: from 2 to 0

  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 31.299904
    leaving at: 59.446918
    permanence: 10.972640
***job and rerouted as:

  EVENT:
    name:       J2
    from:       2
    to:         0
    created:    0.000000
    arrived at: 48.474278
    leaving at: 51.464787
    permanence: 2.990509
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         0
    created:    0.000000
    arrived at: 48.474278
    leaving at: 51.464787
    permanence: 2.990509
***nothing to dequeue:
***Station 0 here: (re)schedule job: from 0 to 1
***job rerouted as:

  EVENT:
    name:       J2
    from:       0
    to:         1
    created:    0.000000
    arrived at: 51.464787
    leaving at: 60.692966
    permanence: 9.228179
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 31.299904
    leaving at: 59.446918
    permanence: 10.972640
*****BEFORE: dequeue the event:
(re)schedule job: from 1 to 2

  EVENT:
    name:       J1
    from:       0
    to:         1
    created:    0.000000
    arrived at: 29.200932
    leaving at: 33.458612
    permanence: 4.257680
*****dequeued job rerouted as:
***Station 2 here: *****new service assigned: 0.075458
(re)schedule job: from 2 to 0

  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 90.904698
    permanence: 31.457780
***job and rerouted as:

  EVENT:
    name:       J3
    from:       2
    to:         0
    created:    0.000000
    arrived at: 59.446918
    leaving at: 59.522376
    permanence: 0.075458
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         0
    created:    0.000000
    arrived at: 59.446918
    leaving at: 59.522376
    permanence: 0.075458
***nothing to dequeue:
***Station 0 here: (re)schedule job: from 0 to 1
***job rerouted as:

  EVENT:
    name:       J3
    from:       0
    to:         1
    created:    0.000000
    arrived at: 59.522376
    leaving at: 61.988964
    permanence: 2.466588
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J2
    from:       0
    to:         1
    created:    0.000000
    arrived at: 51.464787
    leaving at: 60.692966
    permanence: 9.228179
***nothing to dequeue:
***Station 1 here: ***job enqueued
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J3
    from:       0
    to:         1
    created:    0.000000
    arrived at: 59.522376
    leaving at: 61.988964
    permanence: 2.466588
***nothing to dequeue:
***Station 1 here: ***job enqueued
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 90.904698
    permanence: 31.457780
*****BEFORE: dequeue the event:
(re)schedule job: from 1 to 2

  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 38.766069
    leaving at: 39.886999
    permanence: 1.120930
*****dequeued job rerouted as:
***Station 2 here: *****new service assigned: 20.426251

  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 104.117821
    permanence: 13.213123
*****job sliced:
***job sent back as:

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 93.904698
    permanence: 17.426251
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 93.904698
    permanence: 17.426251
***nothing to dequeue:
***Station 2 here: *****job sliced:
***job sent back as:

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 96.904698
    permanence: 14.426251
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 96.904698
    permanence: 14.426251
***nothing to dequeue:
***Station 2 here: *****job sliced:
***job sent back as:

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 99.904698
    permanence: 11.426251
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 99.904698
    permanence: 11.426251
***nothing to dequeue:
***Station 2 here: *****job sliced:
***job sent back as:

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 102.904698
    permanence: 8.426251
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 102.904698
    permanence: 8.426251
***nothing to dequeue:
***Station 2 here: *****job sliced:
***job sent back as:

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 105.904698
    permanence: 5.426251
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 104.117821
    permanence: 13.213123
*****BEFORE: dequeue the event:
(re)schedule job: from 1 to 2

  EVENT:
    name:       J2
    from:       0
    to:         1
    created:    0.000000
    arrived at: 51.464787
    leaving at: 60.692966
    permanence: 9.228179
*****dequeued job rerouted as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       1
    to:         2
    created:    0.000000
    arrived at: 60.692966
    leaving at: 104.351791
    permanence: 0.233970
***job enqueued

  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 104.117821
    permanence: 13.213123
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J2
    from:       1
    to:         2
    created:    0.000000
    arrived at: 60.692966
    leaving at: 104.351791
    permanence: 0.233970
*****BEFORE: dequeue the event:
(re)schedule job: from 1 to 2

  EVENT:
    name:       J3
    from:       0
    to:         1
    created:    0.000000
    arrived at: 59.522376
    leaving at: 61.988964
    permanence: 2.466588
*****dequeued job rerouted as:
***Station 2 here: 
  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 61.988964
    leaving at: 107.712278
    permanence: 3.360487
***job enqueued

  EVENT:
    name:       J2
    from:       1
    to:         2
    created:    0.000000
    arrived at: 60.692966
    leaving at: 104.351791
    permanence: 0.233970
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 105.904698
    permanence: 5.426251
*****dequeue the event:
*****new service assigned: 18.294799

  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 104.117821
    permanence: 13.213123
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 108.904698
    permanence: 15.294799
***job enqueued

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 105.904698
    permanence: 5.426251
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 61.988964
    leaving at: 107.712278
    permanence: 3.360487
***nothing to dequeue:
***Station 2 here: ***job enqueued

  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 61.988964
    leaving at: 107.712278
    permanence: 3.360487
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 108.904698
    permanence: 15.294799
*****dequeue the event:
*****new service assigned: 10.460612

  EVENT:
    name:       J2
    from:       1
    to:         2
    created:    0.000000
    arrived at: 60.692966
    leaving at: 104.351791
    permanence: 0.233970
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 60.692966
    leaving at: 111.904698
    permanence: 7.460612
***job enqueued

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 108.904698
    permanence: 15.294799
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 60.692966
    leaving at: 111.904698
    permanence: 7.460612
*****dequeue the event:

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 105.904698
    permanence: 5.426251
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 114.904698
    permanence: 2.426251
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 60.692966
    leaving at: 111.904698
    permanence: 7.460612
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 114.904698
    permanence: 2.426251
*****dequeue the event:
*****new service assigned: 6.740064

  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 61.988964
    leaving at: 107.712278
    permanence: 3.360487
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 61.988964
    leaving at: 117.904698
    permanence: 3.740064
***job enqueued

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 114.904698
    permanence: 2.426251
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 61.988964
    leaving at: 117.904698
    permanence: 3.740064
*****dequeue the event:

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 108.904698
    permanence: 15.294799
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 120.904698
    permanence: 12.294799
***job enqueued

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 61.988964
    leaving at: 117.904698
    permanence: 3.740064
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 120.904698
    permanence: 12.294799
*****dequeue the event:

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 60.692966
    leaving at: 111.904698
    permanence: 7.460612
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 60.692966
    leaving at: 123.904698
    permanence: 4.460612
***job enqueued

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 120.904698
    permanence: 12.294799
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 60.692966
    leaving at: 123.904698
    permanence: 4.460612
*****dequeue the event:
(re)schedule job: from 2 to 0

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 33.458612
    leaving at: 114.904698
    permanence: 2.426251
*****dequeued job and rerouted as:
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         0
    created:    0.000000
    arrived at: 114.904698
    leaving at: 126.330949
    permanence: 2.426251
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 60.692966
    leaving at: 123.904698
    permanence: 4.460612
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         0
    created:    0.000000
    arrived at: 114.904698
    leaving at: 126.330949
    permanence: 2.426251
*****dequeue the event:

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 61.988964
    leaving at: 117.904698
    permanence: 3.740064
*****job sliced:
*****dequeued job and sent back as:
***Station 0 here: (re)schedule job: from 0 to 1

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 61.988964
    leaving at: 129.330949
    permanence: 0.740064
***job rerouted as:

  EVENT:
    name:       J1
    from:       0
    to:         1
    created:    0.000000
    arrived at: 126.330949
    leaving at: 138.074213
    permanence: 11.743264
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 61.988964
    leaving at: 129.330949
    permanence: 0.740064
*****dequeue the event:

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 120.904698
    permanence: 12.294799
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 132.330949
    permanence: 9.294799
***job enqueued

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 61.988964
    leaving at: 129.330949
    permanence: 0.740064
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 132.330949
    permanence: 9.294799
*****dequeue the event:

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 60.692966
    leaving at: 123.904698
    permanence: 4.460612
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 60.692966
    leaving at: 135.330949
    permanence: 1.460612
***job enqueued

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 132.330949
    permanence: 9.294799
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 60.692966
    leaving at: 135.330949
    permanence: 1.460612
*****dequeue the event:
(re)schedule job: from 2 to 0

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 61.988964
    leaving at: 129.330949
    permanence: 0.740064
*****dequeued job and rerouted as:
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         0
    created:    0.000000
    arrived at: 129.330949
    leaving at: 136.071014
    permanence: 0.740064
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 60.692966
    leaving at: 135.330949
    permanence: 1.460612
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         0
    created:    0.000000
    arrived at: 129.330949
    leaving at: 136.071014
    permanence: 0.740064
*****dequeue the event:

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 132.330949
    permanence: 9.294799
*****job sliced:
*****dequeued job and sent back as:
***Station 0 here: (re)schedule job: from 0 to 1

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 139.071014
    permanence: 6.294799
***job rerouted as:

  EVENT:
    name:       J3
    from:       0
    to:         1
    created:    0.000000
    arrived at: 136.071014
    leaving at: 166.812585
    permanence: 30.741571
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J1
    from:       0
    to:         1
    created:    0.000000
    arrived at: 126.330949
    leaving at: 138.074213
    permanence: 11.743264
***nothing to dequeue:
***Station 1 here: (re)schedule job: from 1 to 2
***job rerouted as:

  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 138.074213
    leaving at: 139.232534
    permanence: 1.158321
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 139.071014
    permanence: 6.294799
*****dequeue the event:
(re)schedule job: from 2 to 0

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 60.692966
    leaving at: 135.330949
    permanence: 1.460612
*****dequeued job and rerouted as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         0
    created:    0.000000
    arrived at: 135.330949
    leaving at: 140.531626
    permanence: 1.460612
***job enqueued

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 139.071014
    permanence: 6.294799
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 138.074213
    leaving at: 139.232534
    permanence: 1.158321
***nothing to dequeue:
***Station 2 here: ***job enqueued

  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 138.074213
    leaving at: 139.232534
    permanence: 1.158321
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         0
    created:    0.000000
    arrived at: 135.330949
    leaving at: 140.531626
    permanence: 1.460612
*****dequeue the event:

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 139.071014
    permanence: 6.294799
*****job sliced:
*****dequeued job and sent back as:
***Station 0 here: (re)schedule job: from 0 to 1

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 143.531626
    permanence: 3.294799
***job rerouted as:

  EVENT:
    name:       J2
    from:       0
    to:         1
    created:    0.000000
    arrived at: 140.531626
    leaving at: 147.469902
    permanence: 6.938276
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 143.531626
    permanence: 3.294799
*****dequeue the event:
*****new service assigned: 0.824854
(re)schedule job: from 2 to 0

  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 138.074213
    leaving at: 139.232534
    permanence: 1.158321
*****dequeued job and rerouted as:
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         0
    created:    0.000000
    arrived at: 139.232534
    leaving at: 144.356480
    permanence: 0.824854
***job enqueued

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 143.531626
    permanence: 3.294799
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         0
    created:    0.000000
    arrived at: 139.232534
    leaving at: 144.356480
    permanence: 0.824854
*****dequeue the event:

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 143.531626
    permanence: 3.294799
*****job sliced:
*****dequeued job and sent back as:
***Station 0 here: (re)schedule job: from 0 to 1

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 147.356480
    permanence: 0.294799
***job rerouted as:

  EVENT:
    name:       J1
    from:       0
    to:         1
    created:    0.000000
    arrived at: 144.356480
    leaving at: 169.315874
    permanence: 24.959394
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 39.886999
    leaving at: 147.356480
    permanence: 0.294799
***nothing to dequeue:
***Station 2 here: (re)schedule job: from 2 to 0
***job and rerouted as:

  EVENT:
    name:       J0
    from:       2
    to:         0
    created:    0.000000
    arrived at: 147.356480
    leaving at: 147.651279
    permanence: 0.294799
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J2
    from:       0
    to:         1
    created:    0.000000
    arrived at: 140.531626
    leaving at: 147.469902
    permanence: 6.938276
***nothing to dequeue:
***Station 1 here: (re)schedule job: from 1 to 2
***job rerouted as:

  EVENT:
    name:       J2
    from:       1
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 158.027405
    permanence: 10.557503
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         0
    created:    0.000000
    arrived at: 147.356480
    leaving at: 147.651279
    permanence: 0.294799
***nothing to dequeue:
***Station 0 here: (re)schedule job: from 0 to 1
***job rerouted as:

  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 147.651279
    leaving at: 155.701375
    permanence: 8.050095
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 147.651279
    leaving at: 155.701375
    permanence: 8.050095
***nothing to dequeue:
***Station 1 here: ***job enqueued
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J2
    from:       1
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 158.027405
    permanence: 10.557503
*****BEFORE: dequeue the event:
(re)schedule job: from 1 to 2

  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 147.651279
    leaving at: 155.701375
    permanence: 8.050095
*****dequeued job rerouted as:
***Station 2 here: *****new service assigned: 19.841287

  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 158.123536
    permanence: 0.096131
*****job sliced:
***job sent back as:

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 161.027405
    permanence: 16.841287
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 158.123536
    permanence: 0.096131
***nothing to dequeue:
***Station 2 here: ***job enqueued

  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 158.123536
    permanence: 0.096131
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 161.027405
    permanence: 16.841287
*****dequeue the event:
*****new service assigned: 12.724844

  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 158.123536
    permanence: 0.096131
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 164.027405
    permanence: 9.724844
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 161.027405
    permanence: 16.841287
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 164.027405
    permanence: 9.724844
*****dequeue the event:

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 161.027405
    permanence: 16.841287
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 167.027405
    permanence: 13.841287
***job enqueued

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 164.027405
    permanence: 9.724844
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J3
    from:       0
    to:         1
    created:    0.000000
    arrived at: 136.071014
    leaving at: 166.812585
    permanence: 30.741571
***nothing to dequeue:
***Station 1 here: (re)schedule job: from 1 to 2
***job rerouted as:

  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 166.812585
    leaving at: 183.446197
    permanence: 16.633612
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 167.027405
    permanence: 13.841287
*****dequeue the event:

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 164.027405
    permanence: 9.724844
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 170.027405
    permanence: 6.724844
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 167.027405
    permanence: 13.841287
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J1
    from:       0
    to:         1
    created:    0.000000
    arrived at: 144.356480
    leaving at: 169.315874
    permanence: 24.959394
***nothing to dequeue:
***Station 1 here: ***job enqueued
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 170.027405
    permanence: 6.724844
*****dequeue the event:

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 167.027405
    permanence: 13.841287
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 173.027405
    permanence: 10.841287
***job enqueued

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 170.027405
    permanence: 6.724844
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 173.027405
    permanence: 10.841287
*****dequeue the event:

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 170.027405
    permanence: 6.724844
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 176.027405
    permanence: 3.724844
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 173.027405
    permanence: 10.841287
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 176.027405
    permanence: 3.724844
*****dequeue the event:

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 173.027405
    permanence: 10.841287
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 179.027405
    permanence: 7.841287
***job enqueued

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 176.027405
    permanence: 3.724844
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 179.027405
    permanence: 7.841287
*****dequeue the event:

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 176.027405
    permanence: 3.724844
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 182.027405
    permanence: 0.724844
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 179.027405
    permanence: 7.841287
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 182.027405
    permanence: 0.724844
*****dequeue the event:

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 179.027405
    permanence: 7.841287
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 185.027405
    permanence: 4.841287
***job enqueued

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 182.027405
    permanence: 0.724844
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 166.812585
    leaving at: 183.446197
    permanence: 16.633612
*****BEFORE: dequeue the event:
(re)schedule job: from 1 to 2

  EVENT:
    name:       J1
    from:       0
    to:         1
    created:    0.000000
    arrived at: 144.356480
    leaving at: 169.315874
    permanence: 24.959394
*****dequeued job rerouted as:
***Station 2 here: 
  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 169.315874
    leaving at: 192.597487
    permanence: 9.151289
***job enqueued

  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 166.812585
    leaving at: 183.446197
    permanence: 16.633612
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 185.027405
    permanence: 4.841287
*****dequeue the event:
(re)schedule job: from 2 to 0

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 155.701375
    leaving at: 182.027405
    permanence: 0.724844
*****dequeued job and rerouted as:
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         0
    created:    0.000000
    arrived at: 182.027405
    leaving at: 185.752250
    permanence: 0.724844
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 185.027405
    permanence: 4.841287
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         0
    created:    0.000000
    arrived at: 182.027405
    leaving at: 185.752250
    permanence: 0.724844
*****dequeue the event:
*****new service assigned: 9.515422

  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 166.812585
    leaving at: 183.446197
    permanence: 16.633612
*****job sliced:
*****dequeued job and sent back as:
***Station 0 here: (re)schedule job: from 0 to 1

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 166.812585
    leaving at: 188.752250
    permanence: 6.515422
***job rerouted as:

  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 185.752250
    leaving at: 203.162742
    permanence: 17.410493
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 166.812585
    leaving at: 188.752250
    permanence: 6.515422
*****dequeue the event:

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 185.027405
    permanence: 4.841287
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 191.752250
    permanence: 1.841287
***job enqueued

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 166.812585
    leaving at: 188.752250
    permanence: 6.515422
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 191.752250
    permanence: 1.841287
*****dequeue the event:

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 166.812585
    leaving at: 188.752250
    permanence: 6.515422
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 166.812585
    leaving at: 194.752250
    permanence: 3.515422
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 191.752250
    permanence: 1.841287
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 169.315874
    leaving at: 192.597487
    permanence: 9.151289
***nothing to dequeue:
***Station 2 here: ***job enqueued

  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 169.315874
    leaving at: 192.597487
    permanence: 9.151289
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 166.812585
    leaving at: 194.752250
    permanence: 3.515422
*****dequeue the event:
(re)schedule job: from 2 to 0

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 147.469902
    leaving at: 191.752250
    permanence: 1.841287
*****dequeued job and rerouted as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         0
    created:    0.000000
    arrived at: 191.752250
    leaving at: 196.593537
    permanence: 1.841287
***job enqueued

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 166.812585
    leaving at: 194.752250
    permanence: 3.515422
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         0
    created:    0.000000
    arrived at: 191.752250
    leaving at: 196.593537
    permanence: 1.841287
*****dequeue the event:
*****new service assigned: 4.964797

  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 169.315874
    leaving at: 192.597487
    permanence: 9.151289
*****job sliced:
*****dequeued job and sent back as:
***Station 0 here: (re)schedule job: from 0 to 1

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 169.315874
    leaving at: 199.593537
    permanence: 1.964797
***job rerouted as:

  EVENT:
    name:       J2
    from:       0
    to:         1
    created:    0.000000
    arrived at: 196.593537
    leaving at: 200.749048
    permanence: 4.155511
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 169.315874
    leaving at: 199.593537
    permanence: 1.964797
*****dequeue the event:

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 166.812585
    leaving at: 194.752250
    permanence: 3.515422
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 166.812585
    leaving at: 202.593537
    permanence: 0.515422
***job enqueued

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 169.315874
    leaving at: 199.593537
    permanence: 1.964797
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J2
    from:       0
    to:         1
    created:    0.000000
    arrived at: 196.593537
    leaving at: 200.749048
    permanence: 4.155511
***nothing to dequeue:
***Station 1 here: (re)schedule job: from 1 to 2
***job rerouted as:

  EVENT:
    name:       J2
    from:       1
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 202.429655
    permanence: 1.680607
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J2
    from:       1
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 202.429655
    permanence: 1.680607
***nothing to dequeue:
***Station 2 here: ***job enqueued

  EVENT:
    name:       J2
    from:       1
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 202.429655
    permanence: 1.680607
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 166.812585
    leaving at: 202.593537
    permanence: 0.515422
*****dequeue the event:
(re)schedule job: from 2 to 0

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 169.315874
    leaving at: 199.593537
    permanence: 1.964797
*****dequeued job and rerouted as:
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         0
    created:    0.000000
    arrived at: 199.593537
    leaving at: 204.558334
    permanence: 1.964797
***job enqueued

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 166.812585
    leaving at: 202.593537
    permanence: 0.515422
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 185.752250
    leaving at: 203.162742
    permanence: 17.410493
***nothing to dequeue:
***Station 1 here: (re)schedule job: from 1 to 2
***job rerouted as:

  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 203.162742
    leaving at: 208.287114
    permanence: 5.124372
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         0
    created:    0.000000
    arrived at: 199.593537
    leaving at: 204.558334
    permanence: 1.964797
*****dequeue the event:
*****new service assigned: 24.081424

  EVENT:
    name:       J2
    from:       1
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 202.429655
    permanence: 1.680607
*****job sliced:
*****dequeued job and sent back as:
***Station 0 here: (re)schedule job: from 0 to 1

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 207.558334
    permanence: 21.081424
***job rerouted as:

  EVENT:
    name:       J1
    from:       0
    to:         1
    created:    0.000000
    arrived at: 204.558334
    leaving at: 207.806174
    permanence: 3.247840
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 207.558334
    permanence: 21.081424
*****dequeue the event:
(re)schedule job: from 2 to 0

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 166.812585
    leaving at: 202.593537
    permanence: 0.515422
*****dequeued job and rerouted as:
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         0
    created:    0.000000
    arrived at: 202.593537
    leaving at: 208.073755
    permanence: 0.515422
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 207.558334
    permanence: 21.081424
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J1
    from:       0
    to:         1
    created:    0.000000
    arrived at: 204.558334
    leaving at: 207.806174
    permanence: 3.247840
***nothing to dequeue:
***Station 1 here: ***job enqueued
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         0
    created:    0.000000
    arrived at: 202.593537
    leaving at: 208.073755
    permanence: 0.515422
*****dequeue the event:

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 207.558334
    permanence: 21.081424
*****job sliced:
*****dequeued job and sent back as:
***Station 0 here: (re)schedule job: from 0 to 1

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 211.073755
    permanence: 18.081424
***job rerouted as:

  EVENT:
    name:       J3
    from:       0
    to:         1
    created:    0.000000
    arrived at: 208.073755
    leaving at: 212.358994
    permanence: 4.285239
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 203.162742
    leaving at: 208.287114
    permanence: 5.124372
*****BEFORE: dequeue the event:
(re)schedule job: from 1 to 2

  EVENT:
    name:       J1
    from:       0
    to:         1
    created:    0.000000
    arrived at: 204.558334
    leaving at: 207.806174
    permanence: 3.247840
*****dequeued job rerouted as:
***Station 2 here: 
  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 208.678629
    permanence: 0.391515
***job enqueued

  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 203.162742
    leaving at: 208.287114
    permanence: 5.124372
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 208.678629
    permanence: 0.391515
***nothing to dequeue:
***Station 2 here: ***job enqueued

  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 208.678629
    permanence: 0.391515
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 211.073755
    permanence: 18.081424
*****dequeue the event:
*****new service assigned: 6.254016

  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 203.162742
    leaving at: 208.287114
    permanence: 5.124372
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 203.162742
    leaving at: 214.073755
    permanence: 3.254016
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 211.073755
    permanence: 18.081424
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J3
    from:       0
    to:         1
    created:    0.000000
    arrived at: 208.073755
    leaving at: 212.358994
    permanence: 4.285239
***nothing to dequeue:
***Station 1 here: (re)schedule job: from 1 to 2
***job rerouted as:

  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 216.887341
    permanence: 4.528347
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 203.162742
    leaving at: 214.073755
    permanence: 3.254016
*****dequeue the event:
*****new service assigned: 14.643019

  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 208.678629
    permanence: 0.391515
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 217.073755
    permanence: 11.643019
***job enqueued

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 203.162742
    leaving at: 214.073755
    permanence: 3.254016
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 216.887341
    permanence: 4.528347
***nothing to dequeue:
***Station 2 here: ***job enqueued

  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 216.887341
    permanence: 4.528347
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 217.073755
    permanence: 11.643019
*****dequeue the event:

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 211.073755
    permanence: 18.081424
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 220.073755
    permanence: 15.081424
***job enqueued

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 217.073755
    permanence: 11.643019
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 220.073755
    permanence: 15.081424
*****dequeue the event:

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 203.162742
    leaving at: 214.073755
    permanence: 3.254016
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 203.162742
    leaving at: 223.073755
    permanence: 0.254016
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 220.073755
    permanence: 15.081424
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 203.162742
    leaving at: 223.073755
    permanence: 0.254016
*****dequeue the event:
*****new service assigned: 18.621026

  EVENT:
    name:       J3
    from:       1
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 216.887341
    permanence: 4.528347
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 226.073755
    permanence: 15.621026
***job enqueued

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 203.162742
    leaving at: 223.073755
    permanence: 0.254016
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 226.073755
    permanence: 15.621026
*****dequeue the event:

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 217.073755
    permanence: 11.643019
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 229.073755
    permanence: 8.643019
***job enqueued

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 226.073755
    permanence: 15.621026
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 229.073755
    permanence: 8.643019
*****dequeue the event:

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 220.073755
    permanence: 15.081424
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 232.073755
    permanence: 12.081424
***job enqueued

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 229.073755
    permanence: 8.643019
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 232.073755
    permanence: 12.081424
*****dequeue the event:
(re)schedule job: from 2 to 0

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 203.162742
    leaving at: 223.073755
    permanence: 0.254016
*****dequeued job and rerouted as:
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         0
    created:    0.000000
    arrived at: 223.073755
    leaving at: 232.327771
    permanence: 0.254016
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 232.073755
    permanence: 12.081424
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         0
    created:    0.000000
    arrived at: 223.073755
    leaving at: 232.327771
    permanence: 0.254016
*****dequeue the event:

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 226.073755
    permanence: 15.621026
*****job sliced:
*****dequeued job and sent back as:
***Station 0 here: (re)schedule job: from 0 to 1

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 235.327771
    permanence: 12.621026
***job rerouted as:

  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 232.327771
    leaving at: 254.382200
    permanence: 22.054429
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 235.327771
    permanence: 12.621026
*****dequeue the event:

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 229.073755
    permanence: 8.643019
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 238.327771
    permanence: 5.643019
***job enqueued

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 235.327771
    permanence: 12.621026
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 238.327771
    permanence: 5.643019
*****dequeue the event:

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 232.073755
    permanence: 12.081424
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 241.327771
    permanence: 9.081424
***job enqueued

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 238.327771
    permanence: 5.643019
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 241.327771
    permanence: 9.081424
*****dequeue the event:

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 235.327771
    permanence: 12.621026
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 244.327771
    permanence: 9.621026
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 241.327771
    permanence: 9.081424
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 244.327771
    permanence: 9.621026
*****dequeue the event:

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 238.327771
    permanence: 5.643019
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 247.327771
    permanence: 2.643019
***job enqueued

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 244.327771
    permanence: 9.621026
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 247.327771
    permanence: 2.643019
*****dequeue the event:

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 241.327771
    permanence: 9.081424
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 250.327771
    permanence: 6.081424
***job enqueued

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 247.327771
    permanence: 2.643019
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 250.327771
    permanence: 6.081424
*****dequeue the event:

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 244.327771
    permanence: 9.621026
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 253.327771
    permanence: 6.621026
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 250.327771
    permanence: 6.081424
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 253.327771
    permanence: 6.621026
*****dequeue the event:
(re)schedule job: from 2 to 0

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 207.806174
    leaving at: 247.327771
    permanence: 2.643019
*****dequeued job and rerouted as:
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         0
    created:    0.000000
    arrived at: 247.327771
    leaving at: 255.970790
    permanence: 2.643019
***job enqueued

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 253.327771
    permanence: 6.621026
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 232.327771
    leaving at: 254.382200
    permanence: 22.054429
***nothing to dequeue:
***Station 1 here: (re)schedule job: from 1 to 2
***job rerouted as:

  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 254.382200
    leaving at: 256.319487
    permanence: 1.937287
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         0
    created:    0.000000
    arrived at: 247.327771
    leaving at: 255.970790
    permanence: 2.643019
*****dequeue the event:

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 250.327771
    permanence: 6.081424
*****job sliced:
*****dequeued job and sent back as:
***Station 0 here: (re)schedule job: from 0 to 1

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 258.970790
    permanence: 3.081424
***job rerouted as:

  EVENT:
    name:       J1
    from:       0
    to:         1
    created:    0.000000
    arrived at: 255.970790
    leaving at: 262.015166
    permanence: 6.044377
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 254.382200
    leaving at: 256.319487
    permanence: 1.937287
***nothing to dequeue:
***Station 2 here: ***job enqueued

  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 254.382200
    leaving at: 256.319487
    permanence: 1.937287
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 258.970790
    permanence: 3.081424
*****dequeue the event:

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 253.327771
    permanence: 6.621026
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 261.970790
    permanence: 3.621026
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 258.970790
    permanence: 3.081424
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 261.970790
    permanence: 3.621026
*****dequeue the event:
*****new service assigned: 3.710552

  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 254.382200
    leaving at: 256.319487
    permanence: 1.937287
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 254.382200
    leaving at: 264.970790
    permanence: 0.710552
***job enqueued

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 261.970790
    permanence: 3.621026
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J1
    from:       0
    to:         1
    created:    0.000000
    arrived at: 255.970790
    leaving at: 262.015166
    permanence: 6.044377
***nothing to dequeue:
***Station 1 here: (re)schedule job: from 1 to 2
***job rerouted as:

  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 262.015166
    leaving at: 267.458723
    permanence: 5.443557
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 254.382200
    leaving at: 264.970790
    permanence: 0.710552
*****dequeue the event:

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 258.970790
    permanence: 3.081424
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 267.970790
    permanence: 0.081424
***job enqueued

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 254.382200
    leaving at: 264.970790
    permanence: 0.710552
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 262.015166
    leaving at: 267.458723
    permanence: 5.443557
***nothing to dequeue:
***Station 2 here: ***job enqueued

  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 262.015166
    leaving at: 267.458723
    permanence: 5.443557
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 267.970790
    permanence: 0.081424
*****dequeue the event:

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 261.970790
    permanence: 3.621026
*****job sliced:
*****dequeued job and sent back as:
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 270.970790
    permanence: 0.621026
***job enqueued

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 267.970790
    permanence: 0.081424
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 270.970790
    permanence: 0.621026
*****dequeue the event:
(re)schedule job: from 2 to 0

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 254.382200
    leaving at: 264.970790
    permanence: 0.710552
*****dequeued job and rerouted as:
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         0
    created:    0.000000
    arrived at: 264.970790
    leaving at: 271.681342
    permanence: 0.710552
***job enqueued

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 270.970790
    permanence: 0.621026
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         0
    created:    0.000000
    arrived at: 264.970790
    leaving at: 271.681342
    permanence: 0.710552
*****dequeue the event:
*****new service assigned: 13.010500

  EVENT:
    name:       J1
    from:       1
    to:         2
    created:    0.000000
    arrived at: 262.015166
    leaving at: 267.458723
    permanence: 5.443557
*****job sliced:
*****dequeued job and sent back as:
***Station 0 here: (re)schedule job: from 0 to 1

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 262.015166
    leaving at: 274.681342
    permanence: 10.010500
***job rerouted as:

  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 271.681342
    leaving at: 281.200823
    permanence: 9.519481
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 262.015166
    leaving at: 274.681342
    permanence: 10.010500
*****dequeue the event:
(re)schedule job: from 2 to 0

  EVENT:
    name:       J2
    from:       2
    to:         2
    created:    0.000000
    arrived at: 200.749048
    leaving at: 267.970790
    permanence: 0.081424
*****dequeued job and rerouted as:
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         0
    created:    0.000000
    arrived at: 267.970790
    leaving at: 274.762766
    permanence: 0.081424
***job enqueued

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 262.015166
    leaving at: 274.681342
    permanence: 10.010500
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J2
    from:       2
    to:         0
    created:    0.000000
    arrived at: 267.970790
    leaving at: 274.762766
    permanence: 0.081424
*****dequeue the event:
(re)schedule job: from 2 to 0

  EVENT:
    name:       J3
    from:       2
    to:         2
    created:    0.000000
    arrived at: 212.358994
    leaving at: 270.970790
    permanence: 0.621026
*****dequeued job and rerouted as:
***Station 0 here: (re)schedule job: from 0 to 1

  EVENT:
    name:       J3
    from:       2
    to:         0
    created:    0.000000
    arrived at: 270.970790
    leaving at: 275.383792
    permanence: 0.621026
***job rerouted as:

  EVENT:
    name:       J2
    from:       0
    to:         1
    created:    0.000000
    arrived at: 274.762766
    leaving at: 306.270006
    permanence: 31.507240
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J3
    from:       2
    to:         0
    created:    0.000000
    arrived at: 270.970790
    leaving at: 275.383792
    permanence: 0.621026
*****dequeue the event:

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 262.015166
    leaving at: 274.681342
    permanence: 10.010500
*****job sliced:
*****dequeued job and sent back as:
***Station 0 here: (re)schedule job: from 0 to 1

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 262.015166
    leaving at: 278.383792
    permanence: 7.010500
***job rerouted as:

  EVENT:
    name:       J3
    from:       0
    to:         1
    created:    0.000000
    arrived at: 275.383792
    leaving at: 315.599336
    permanence: 40.215543
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 262.015166
    leaving at: 278.383792
    permanence: 7.010500
***nothing to dequeue:
***Station 2 here: *****job sliced:
***job sent back as:

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 262.015166
    leaving at: 281.383792
    permanence: 4.010500
engine:
Processing the event
***Station 0 here: 
  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 271.681342
    leaving at: 281.200823
    permanence: 9.519481
***nothing to dequeue:
***Station 1 here: (re)schedule job: from 1 to 2
***job rerouted as:

  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 281.200823
    leaving at: 286.609103
    permanence: 5.408280
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 262.015166
    leaving at: 281.383792
    permanence: 4.010500
***nothing to dequeue:
***Station 2 here: *****job sliced:
***job sent back as:

  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 262.015166
    leaving at: 284.383792
    permanence: 1.010500
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         2
    created:    0.000000
    arrived at: 262.015166
    leaving at: 284.383792
    permanence: 1.010500
***nothing to dequeue:
***Station 2 here: (re)schedule job: from 2 to 0
***job and rerouted as:

  EVENT:
    name:       J1
    from:       2
    to:         0
    created:    0.000000
    arrived at: 284.383792
    leaving at: 285.394293
    permanence: 1.010500
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J1
    from:       2
    to:         0
    created:    0.000000
    arrived at: 284.383792
    leaving at: 285.394293
    permanence: 1.010500
***nothing to dequeue:
***Station 0 here: (re)schedule job: from 0 to 1
***job rerouted as:

  EVENT:
    name:       J1
    from:       0
    to:         1
    created:    0.000000
    arrived at: 285.394293
    leaving at: 298.802810
    permanence: 13.408517
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J0
    from:       1
    to:         2
    created:    0.000000
    arrived at: 281.200823
    leaving at: 286.609103
    permanence: 5.408280
***nothing to dequeue:
***Station 2 here: *****new service assigned: 5.518213
*****job sliced:
***job sent back as:

  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 281.200823
    leaving at: 289.609103
    permanence: 2.518213
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         2
    created:    0.000000
    arrived at: 281.200823
    leaving at: 289.609103
    permanence: 2.518213
***nothing to dequeue:
***Station 2 here: (re)schedule job: from 2 to 0
***job and rerouted as:

  EVENT:
    name:       J0
    from:       2
    to:         0
    created:    0.000000
    arrived at: 289.609103
    leaving at: 292.127316
    permanence: 2.518213
engine:
Processing the event
***Station 2 here: 
  EVENT:
    name:       J0
    from:       2
    to:         0
    created:    0.000000
    arrived at: 289.609103
    leaving at: 292.127316
    permanence: 2.518213
***nothing to dequeue:
***Station 0 here: (re)schedule job: from 0 to 1
***job rerouted as:

  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 292.127316
    leaving at: 294.465715
    permanence: 2.338398
engine:
Hit regeneration
