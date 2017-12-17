Creating the system ---
--- At station: 
(re)schedule job: from 0 to 1

  STATION:
    id:             0
    clients inside: 7
    arrivals:       7
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
    leaving at: 18.680104
    permanence: 18.680104
Generated the event:
(re)schedule job: from 0 to 1

  EVENT:
    name:       J2
    from:       0
    to:         1
    created:    0.000000
    arrived at: 0.000000
    leaving at: 119.652733
    permanence: 119.652733
Generated the event:
(re)schedule job: from 0 to 1

  EVENT:
    name:       J3
    from:       0
    to:         1
    created:    0.000000
    arrived at: 0.000000
    leaving at: 59.337876
    permanence: 59.337876
Generated the event:
(re)schedule job: from 0 to 1

  EVENT:
    name:       J4
    from:       0
    to:         1
    created:    0.000000
    arrived at: 0.000000
    leaving at: 28.668535
    permanence: 28.668535
Generated the event:
(re)schedule job: from 0 to 1

  EVENT:
    name:       J5
    from:       0
    to:         1
    created:    0.000000
    arrived at: 0.000000
    leaving at: 40.032123
    permanence: 40.032123
Generated the event:

  EVENT:
    name:       J6
    from:       0
    to:         1
    created:    0.000000
    arrived at: 0.000000
    leaving at: 17.030720
    permanence: 17.030720
--- At station: 

  STATION:
    id:             1
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
***Station 1 here: (re)schedule job: from 1 to 0
***job rerouted as:

  EVENT:
    name:       J0
    from:       1
    to:         0
    created:    0.000000
    arrived at: 0.000000
    leaving at: 14.307346
    permanence: 14.307346
engine:
Processing the event
***Station 1 here: 
  EVENT:
    name:       J0
    from:       1
    to:         0
    created:    0.000000
    arrived at: 0.000000
    leaving at: 14.307346
    permanence: 14.307346
***nothing to dequeue:
***Station 0 here: (re)schedule job: from 0 to 1
***job rerouted as:

  EVENT:
    name:       J0
    from:       0
    to:         1
    created:    0.000000
    arrived at: 14.307346
    leaving at: 18.791066
    permanence: 4.483720
engine:
Hit regeneration
