// // Exaple from class
// class SampleSimObject : public SimObject{
// private:
//     class SampleEvent : public Event{
//     private:
//         SampleSimObject *sso;
//     public:
//         SampleEvent(SampleSimObject *s) : Event() { sso = s; }
//         void process() overide { sso->process(); }
//     };
//     SampleEvent * e;
// protected:
// public:
//     SampleSimObject();
//     void process();
// };
