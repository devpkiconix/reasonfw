/*
 module type MachineType = {
   type context_t;
   type state_name_t;
   type event_name_t;
   type event_data_t;
   type predicate_t;


   type machine = | Empty | Mc({
     /* current:  */
     state_name_t,
     /* context:  */
     context_t,
   });

   let addTransition:
     (
       state_name_t,
       event_name_t,
       option(predicate_t),
       state_name_t,
       machine
     ) =>
     machine;
   let empty: unit => machine;
   let start: (/*initial:*/ state_name_t, machine) => machine;
   let inject: (/* event */ event_name_t, event_data_t, machine) => machine;
 };

 module MakeMc = (Mc: MachineType) => {
     /* Mutually recursive types */
   type transition_t = {
     event: Mc.event_name_t,
     predicate: option(Mc.predicate_t),
     target: option(Mc.state_name_t),
   }
   and state_t = {
     id: Mc.state_name_t,
     transitions: list(transition_t),
     isFinal: bool,
   };
   type event_t;

   type machineCfg = | Empty | Machine(list(state_t);

   let empty = () => {
     Empty;
   };

   let start = (initial: Mc.state_name_t, Mc.machine) => {

   }
   let inject = (event: event_name_t, data: Mc.event_data_t, mc: Mc.machine) => {

   }
 };

 module ExampleMc_t: MachineType = {
   type context_t = {something: string};
   type predicate_t;

   type event_name_t =
     | EONE
     | ETWO
     | ETHREE;
   type state_name_t =
     | SONE
     | STWO
     | STHREE;
 };

 module ExampleMc = Make(ExampleMc_t);*/