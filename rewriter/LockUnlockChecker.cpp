// from the cfe-dev posted tutorial:
#include <string>

#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CallEvent.h"
#include "clang/StaticAnalyzer/Core/CheckerRegistry.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"

using namespace clang;
using namespace ento;

REGISTER_TRAIT_WITH_PROGRAMSTATE(LockState, bool);

namespace {
   class LockUnlockChecker : public Checker<check::PreCall> {
      OwningPtr<BugType> NoUnlockBugType;
      OwningPtr<BugType> DoubleLockBugType;
      OwningPtr<BugType> DoubleUnlockBugType;

      public:
      LockUnlockChecker(void) {
         NoUnlockBugType.reset(new BugType("Failure to call unlock", "Example Plugin"));
         DoubleLockBugType.reset(new BugType("Double Lock", "Example Plugin"));
         DoubleUnlockBugType.reset(new BugType("Double Unlock", "Example Plugin"));
      }
      
      void checkPreCall(const CallEvent & call, CheckerContext &C) const {
         const IdentifierInfo * identInfo = call.getCalleeIdentifier();
         if(!identInfo) {
            return;
         }
         std::string funcName = std::string(identInfo->getName());

         ProgramStateRef state = C.getState();

         if(funcName.compare("lock") == 0) {
            bool currentlyLocked = state->get<LockState>();
            if(currentlyLocked) {
               ExplodedNode * bugloc = C.generateSink();
               if(bugloc) {
                  BugReport * bug = new BugReport(*DoubleLockBugType,
                        "Call to lock when already locked", bugloc);
                  C.emitReport(bug);
               }
            }
            state = state->set<LockState>(true);
            C.addTransition(state);
         } else if(funcName.compare("unlock") == 0) {
            bool currentlyLocked = state->get<LockState>();
            if(!currentlyLocked) {
               ExplodedNode * bugloc = C.generateSink();
               if(bugloc) {
                  BugReport * bug = new BugReport(*DoubleUnlockBugType,
                        "Call to unlock when already unlocked", bugloc);
                  C.emitReport(bug);
               }
            }
            state = state->set<LockState>(false);
            C.addTransition(state);
         }

      }
      
      void checkEndPath(CheckerContext &C) const {
         ProgramStateRef state = C.getState();

         bool currentlyLocked = state->get<LockState>();
         if(currentlyLocked) {
            ExplodedNode * bugloc = C.generateSink();
            if(bugloc) {
               BugReport * bug = new BugReport(*NoUnlockBugType,
                     "Return from function without calling unlock", bugloc);
               C.emitReport(bug);
            }
         }
      }
   };
}

extern "C" const char clang_analyzerAPIVersionString[] = CLANG_ANALYZER_API_VERSION_STRING;

extern "C" void clang_registerCheckers(CheckerRegistry &registry) {
   registry.addChecker<LockUnlockChecker>("example.LockUnlockChecker", "Checker for use of lock()/unlock()");
}
