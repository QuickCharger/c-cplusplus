#include <iostream>

using namespace std;

class MisDepartment {
public:
	void submitNetworkRequest() {
		m_nState = Received;
	}
	bool checkOnStatus() {
		m_nState++;
		if (m_nState == Complete)
			return 1;
		return 0;
	}
private:
	enum States {
		Received, DenyAllKnowledge, ReferClientToFacilities,
		FacilitiesHasNotSentPaperwork, ElectricianIsNotDone,
		ElectricianDidItWrong, DispatchTechnician, SignedOff,
		DoesNotWork, FixElectriciansWiring, Complete
	};
	int m_nState;
};

class ElectricianUnion {
public:
	void submitNetworkRequest() {
		m_nState = Received;
	}
	bool checkOnStatus() {
		m_nState++;
		if (m_nState == Complete)
			return 1;
		return 0;
	}
private:
	enum States {
		Received, RejectTheForm, SizeTheJob, SmokeAndJokeBreak,
		WaitForAuthorization, DoTheWrongJob, BlameTheEngineer, WaitToPunchOut,
		DoHalfAJob, ComplainToEngineer, GetClarification, CompleteTheJob,
		TurnInThePaperWork, Complete
	};
	int m_nState;
};

class FacilitiesDepartment {
public:
	void submitNetworkRequest() {
		m_nState = Received;
	}
	bool checkOnStatus() {
		m_nState++;
		if (m_nState == Complete)
			return 1;
		return 0;
	}
private:
	enum States {
		Received, AssignToEngineer, EngineerResearches, RequestIsNotPossible,
		EngineerLeavesCompany, AssignToNewEngineer, NewEngineerResearches,
		ReassignEngineer, EngineerReturns, EngineerResearchesAgin,
		EngineerFillsOutPaperWork, Complete
	};
	int m_nState;
};

class FacilitiesFacade {
public:
	FacilitiesFacade() {
		m_nCount = 0;
	}
	void submitNetworkRequest() {
		m_nState = Received;
	}
	bool checkOnStatus() {
		m_nCount++;
		if (m_nState == Received) {
			m_nState++;
			m_Engineer.submitNetworkRequest();
			cout << "submitted to Facilities - " << m_nCount << " phone calls so far" << endl;
		}
		else if (m_nState == SubmitToEngineer && m_Engineer.checkOnStatus()) {
			m_nState++;
			m_Electrician.submitNetworkRequest();
			cout << "submitted to Electrician - " << m_nCount << " phone calls so far" << endl;
		}
		else if (m_nState == SubmitToElectrician && m_Electrician.checkOnStatus()) {
			m_nState++;
			m_Technician.submitNetworkRequest();
			cout << "submitted to MIS - " << m_nCount << " phone calls so far" << endl;
		}
		else if (m_nState == SubmitToTechnician && m_Technician.checkOnStatus()) {
			return 1;
		}
		return 0;
	}
	int getNumberOfCalls() {
		return m_nCount;
	}
private:
	enum Stats {
		Received, SubmitToEngineer, SubmitToElectrician, SubmitToTechnician
	};
	int m_nState;
	int m_nCount;
	FacilitiesDepartment m_Engineer;
	ElectricianUnion m_Electrician;
	MisDepartment m_Technician;
};

int main() {
	FacilitiesFacade facilities;
	facilities.submitNetworkRequest();

	while (!facilities.checkOnStatus());
	cout << "job completed after only " << facilities.getNumberOfCalls() << " phone calls" << endl;

	getchar();
	return 0;
}
