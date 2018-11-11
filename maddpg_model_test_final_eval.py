import tensorflow as tf
import numpy as np
from keras.models import Model
from keras.layers import Dense,Input,BatchNormalization,Add,Activation,Lambda, concatenate
from keras.initializers import normal
from keras.optimizers import Adam
import keras.backend as K
# from keras backend import manual_variable_initializion

#from utils import onehot_argmax_layer

class ActorNetwork(object):
	"""
	Implements actor network
	"""
	def __init__(self,sess,state_dim,action_dim,lr,tau):
		self.sess = sess
		K.set_session(sess)
		K.set_learning_phase(1)
		K.manual_variable_initialization(True)
		self.state_dim = state_dim
		self.action_dim = action_dim
		# self.state_dim = 3
		# self.action_dim = 2
		self.lr =  lr
		self.tau = tau
		self.mainModel,self.mainModel_weights,self.mainModel_state = self._build_model()
		self.targetModel,self.targetModel_weights,_ = self._build_model()
		self.action_gradient = tf.placeholder(tf.float32,[None,self.action_dim])
		self.params_grad = tf.gradients(self.mainModel.output,self.mainModel_weights,-self.action_gradient)
		grads = zip(self.params_grad,self.mainModel_weights)
		self.optimize = tf.train.AdamOptimizer(self.lr).apply_gradients(grads)
		self.sess.run(tf.global_variables_initializer())

	def _build_model(self):
		input_obs = Input(shape=(self.state_dim,))
		h = Dense(64, kernel_initializer='he_normal')(input_obs)
		h = Activation('relu')(h)
		#h = BatchNormalization()(h)
		h = Dense(64, kernel_initializer='he_normal')(h)
		h = Activation('relu')(h)
		h = BatchNormalization()(h)
		# load_alloc = Dense(1,activation='tanh',init=lambda shape, name: normal(shape, scale=1e-4, name=name))(h)  
        # load_number = Dense(1,activation='sigmoid',init=lambda shape, name: normal(shape, scale=1e-4, name=name))(h)
		# V = merge([load_alloc,load_number],mode='concat')          
		# h = Dense(self.action_dim, activation='softmax', init=lambda shape: normal(shape, mean=0, stddev=1))(h)
		load_alloc = Dense(1, activation='sigmoid', kernel_initializer='he_normal')(h)
		load_number = Dense(1, activation='linear', kernel_initializer='RandomNormal')(h)
		V = concatenate([load_alloc,load_number])          
		# h = Activation('softmax')(h)
		# pred = Lambda(lambda h: tf.contrib.distributions.RelaxedOneHotCategorical(2,probs=h).sample())(h)
		model = Model(inputs=input_obs,outputs=V)
		model.compile(optimizer='Adam',loss='mean_squared_error')
		return model,model.trainable_weights,input_obs

	def act(self,state,noise):
		act = self.mainModel.predict(state) + noise
		return act

	def predict_target(self,state):
		return self.targetModel.predict(state)

	def predict(self,state):
		return self.mainModel.predict(state)

	def update_target(self):
		wMain =  np.asarray(self.mainModel.get_weights())
		wTarget = np.asarray(self.targetModel.get_weights())
		for i in range(len(wMain)):
			wTarget[i] = self.tau*wMain[i] + (1-self.tau)*wTarget[i]
		self.targetModel.set_weights(wTarget)

	def train(self,state,action_grad):
		self.sess.run(self.optimize,feed_dict = {self.mainModel_state: state, self.action_gradient: action_grad})


class CriticNetwork(object):
	def __init__(self,sess,num_agents,state_dim,action_dim,lr,tau,gamma):
		self.sess = sess
		K.set_session(sess)
		K.set_learning_phase(1)
		K.manual_variable_initialization(True)
		self.state_dim = state_dim
		self.action_dim = action_dim
		self.lr =  lr
		self.tau = tau
		self.num_agents = num_agents
		self.gamma  =  gamma
		self.mainModel,self.state,self.actions = self._build_model()
		self.targetModel,_,_ = self._build_model()
		self.action_grads  = tf.gradients(self.mainModel.output,self.actions)
		self.sess.run(tf.global_variables_initializer())

	def _build_model(self):
		input_obs = Input(shape=(self.state_dim,))
		input_actions = Input(shape=(self.action_dim,))
		h = Dense(64, kernel_initializer='he_normal')(input_obs)
		h = Activation('relu')(h)
		#h = BatchNormalization()(h)
		action_abs = Dense(64)(input_actions)
		temp1 = Dense(64, kernel_initializer='he_normal')(h)
		#action_abs = Activation('relu')(action_abs)
		#action_abs = BatchNormalization()(action_abs)
		h = Add()([temp1,action_abs])
		#h = Dense(64)(h)
		h = Activation('relu')(h)
		h = BatchNormalization()(h)
		pred = Dense(2,kernel_initializer='random_uniform')(h)
		model = Model(inputs=[input_obs,input_actions],outputs=pred)
		model.compile(optimizer='Adam',loss='mean_squared_error')
		return model,input_obs,input_actions

	def action_gradients(self,states,actions):
		return self.sess.run(self.action_grads,feed_dict={self.state: states, self.actions: actions})[0]

	def update_target(self):
		wMain =  np.asarray(self.mainModel.get_weights())
		wTarget = np.asarray(self.targetModel.get_weights())
		for i in range(len(wMain)):
			wTarget[i] = self.tau*wMain[i] + (1-self.tau)*wTarget[i]
		self.targetModel.set_weights(wTarget)

	def predict_target(self, state, actions):
		return self.targetModel.predict([state,actions])

	def predict(self, state, actions):
		x = np.ndarray((actions.shape[1],self.action_dim))
		for j in range(actions.shape[1]):
			x[j] = np.concatenate([y[j] for y in actions])
		return self.mainModel.predict([state,x])

	def train(self, state, actions, labels):
		self.mainModel.train_on_batch([state,actions],labels)