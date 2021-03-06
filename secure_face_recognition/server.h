/*
SeComLib
Copyright 2012-2013 TU Delft, Information Security & Privacy Lab (http://isplab.tudelft.nl/)

Contributors:
Inald Lagendijk (R.L.Lagendijk@TUDelft.nl)
Mihai Todor (todormihai@gmail.com)
Thijs Veugen (P.J.M.Veugen@tudelft.nl)
Zekeriya Erkin (z.erkin@tudelft.nl)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
/**
@file secure_face_recognition/server.h
@brief Definition of class Server.
@author Mihai Todor (todormihai@gmail.com)
*/

#ifndef SERVER_HEADER_GUARD
#define SERVER_HEADER_GUARD

//include our headers
#include "utils/config.h"
#include "core/big_integer.h"
#include "core/paillier.h"
#include "core/dgk.h"

#include "secure_face_recognition_utils/secure_comparison_server.h"

namespace SeComLib {
using namespace Core;
using namespace SecureFaceRecognitionUtils;

namespace SecureFaceRecognition {
	//forward-declare required classes
	class Client;

	/**
	@brief Server
	*/
	class Server {
	public:
		/// Constructor
		Server (const PaillierPublicKey &paillierPublicKey, const DgkPublicKey &dgkPublicKey);

		/// Destructor - void implementation
		~Server () {}

		/// Computes the relation between the inputs
		Paillier::Ciphertext SecureComparison (const Paillier::Ciphertext &a, const Paillier::Ciphertext &b) const;

		/// Sets a reference to the Privacy Service Provider
		void SetClient (const std::shared_ptr<const Client> &client);

		/// Getter for this->secureComparisonServer
		const std::shared_ptr<SecureComparisonServer> &GetSecureComparisonServer () const;

	private:
		/// A reference to the Client
		std::weak_ptr<const Client> client;

		/// Paillier crypto provider
		Paillier paillierCryptoProvider;

		/// DGK crypto provider
		Dgk dgkCryptoProvider;

		/// A reference to the SecureComparisonServer
		const std::shared_ptr<SecureComparisonServer> secureComparisonServer;

		/// Service Provider configuration path
		static const std::string configurationPath;

		/// Copy constructor - not implemented
		Server (Server const &);

		/// Copy assignment operator - not implemented
		Server operator= (Server const &);
	};
}//namespace SecureFaceRecognition
}//namespace SeComLib

#endif//SERVER_HEADER_GUARD